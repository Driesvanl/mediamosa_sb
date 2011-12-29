<?php
/**
 * MediaMosa is a Full Featured, Webservice Oriented Media Management and
 * Distribution platform (http://mediamosa.org)
 *
 * Copyright (C) 2012 SURFnet BV (http://www.surfnet.nl)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, you can find it at:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 */

/**
 * Step 1: Upload file to MediaMosa.
 */
function mediamosa_sb_asset_upload_form($form, &$form_state) {
  // If you are familiar with how browsers handle files, you know that
  // enctype="multipart/form-data" is required. Drupal takes care of that, so
  // you don't need to include it yourself.
  drupal_set_title(t('Step 1/4: Upload'));

  // Try to create upload ticket.
  $result = MediaMosaCkConnectorWrapper::request_create_upload_ticket();
  if (!$result) {
    $form['upload'] = array(
      '#markup' => t('Unable to upload to MediaMosa; @reason', array('@reason' => mediamosa_ck::get_connector_last_error_text())),
    );

    return $form;
  }

  // Get upload URL.
  $upload_url = $result['action'];

/*
  drupal 6;
  <input type="file" name="file"  class="form-file required" id="edit-file" size="60" />

  drupal 7
  <input type="file" id="edit-file" name="files[file]" size="60" class="form-file" />
*/

  // Because we override.
  $form_state['has_file_element'] = TRUE;

  // FIXME: Hack to make it work with single array file upload to mediamosa.
  // To make it work with MediaMosa single array upload result.
  $form['file'] = array(
    '#markup' => '<input type="file" id="edit-file" name="file" size="60" class="form-file" />',
    '#title' => t('Upload your file'),
    // @todo: make setting.
    '#description' => t('Maximum size of 2,0 GB, MOV, AVI'),
  );

  // Redirect value, we need to redirect back after upload so we can add it to
  // Drupal.
  $form['redirect_uri'] = array(
    '#type' => 'hidden',
    '#value' => url('mediamosa/upload/edit/' . rawurlencode($result['asset_id']) . '/' . rawurlencode($result['mediafile_id']), array('absolute' => TRUE)),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#description' => t('Upload your file'),
    '#value' => t('Upload'),
  );

  $form['#action'] = $upload_url;

  // Merge with other options in for upload (turned off for now).
  $form = array_merge(module_invoke_all('media_mediamosa_upload_collect'), $form);

  return $form;
}

/**
 * The step 2/3/4 form.
 */
function mediamosa_sb_asset_upload_steps_form($form, &$form_state, $asset_id, $mediafile_id) {
  // Initialize a description of the steps for the steps.
  if (empty($form_state['step'])) {
    // Store them. Even if the user tries something with url, he can only handle
    // own assets.
    $form_state['asset_id'] = $asset_id;
    $form_state['mediafile_id'] = $mediafile_id;

    $form_state['step'] = 1;
    // This array contains the function to be called at each step to get the
    // relevant form elements. It will also store state information for each
    // step.
    $form_state['step_information'] = array(
      1 => array(
        'form' => 'mediamosa_sb_asset_upload_step_metadata_form',
        'name' => 'Metadata',
      ),
      2 => array(
        'form' => 'mediamosa_sb_asset_upload_step_access_form',
        'name' => 'Access & Visibility',
      ),
      3 => array(
        'form' => 'mediamosa_sb_asset_upload_step_transcode_form',
        'name' => 'Define formats',
      ),
    );
  }

  $step = $form_state['step'];
  $name = $form_state['step_information'][$step]['name'];

  // Set title.
  drupal_set_title(t('Step @step/4: @name', array('@step' => $step + 1, '@name' => $name)));

  // Call the function named in $form_state['step_information'] to get the
  // form elements to display for this step.
  $form = $form_state['step_information'][$step]['form']($form, $form_state);

  // Show the Next button only if there are more steps defined.
  if ($step < count($form_state['step_information'])) {
    // The Next button should be included on every step
    $form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#name' => 'next',
      '#submit' => array('_mediamosa_sb_asset_upload_steps_next_submit'),
    );

    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#name' => 'prev',
      '#submit' => array('_mediamosa_sb_asset_upload_steps_cancel_submit'),
      '#limit_validation_errors' => array(),
    );

    // Include each validation function defined for the different steps.
    if (function_exists($form_state['step_information'][$step]['form'] . '_validate')) {
      $form['next']['#validate'] = array($form_state['step_information'][$step]['form'] . '_validate');
    }
  }
  else {
    // Just in case there are no more steps, we use the default submit handler
    // of the form steps.
    $form['finish'] = array(
      '#type' => 'submit',
      '#value' => t('Finish'),
      '#submit' => array('_mediamosa_sb_asset_upload_steps_finish_submit'),
    );
  }

  return $form;
}

/**
 * Submit handler for the "cancel" button.
 */
function _mediamosa_sb_asset_upload_steps_cancel_submit($form, &$form_state) {
  // Go back to start.
  drupal_goto('mediamosa/upload');
}

/**
 * Submit handler for the 'next' button.
 * - Saves away $form_state['values']
 * - Increments the step count.
 * - Replace $form_state['values'] from the last time we were at this page
 *   or with array() if we haven't been here before.
 * - Force form rebuild.
 *
 * @param $form
 * @param $form_state
 */
function _mediamosa_sb_asset_upload_steps_next_submit($form, &$form_state) {
  $form_state['step_information'][$form_state['step']]['stored_values'] = $form_state['values'];

  if ($form_state['step'] < count($form_state['step_information'])) {
    $form_state['step']++;

    if (!empty($form_state['step_information'][$form_state['step']]['stored_values'])) {
      $form_state['values'] = $form_state['step_information'][$form_state['step']]['stored_values'];
    }
    else {
      $form_state['values'] = array();
    }

    $form_state['rebuild'] = TRUE;  // Force rebuild with next step.
    return;
  }
}

/**
 * The metadata step form.
 */
function mediamosa_sb_asset_upload_step_metadata_form($form, &$form_state) {
  $form = array();

  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic Information'),
  );

  $form['basic']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
  );

  $form['basic']['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#required' => FALSE,
  );

  $form['collections'] = array(
    '#type' => 'fieldset',
    '#title' => t('Collections'),
  );

  $form['collections']['collections'] = array(
    '#type' => 'select',
    '#title' => t('My collections'),
    '#required' => FALSE,
    '#size'=> 5,
    '#options' => array(
       0 => t('Farmacologie dagen 2011'),
       1 => t('Rondom Uithof'),
     ),
  );

  $form['add'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional metadata <span>(According Dublin Metadata Initiative)</span>'),
  );

  $form['add']['dc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dublin core'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['add']['dc']['type'] = array(
    '#type' => 'textfield',
    '#title' => t('Type'),
    '#required' => FALSE,
    '#description' => t('The nature or genre of the resource e.g. Image, MovingImage'),
  );

  $form['add']['dc']['format'] = array(
    '#type' => 'textfield',
    '#title' => t('Format'),
    '#required' => FALSE,
    '#description' => t('The file format, physical medium e.g. video, image'),
  );

  $form['add']['dc']['language'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#required' => FALSE,
    '#description' => t('The language of the resource'),
    '#options'  => mediamosa_sb::get_metdata_languages_options(),
  );

  $form['add']['dc']['creator'] = array(
    '#type' => 'textfield',
    '#title' => t('Creator'),
    '#required' => FALSE,
    '#description' => t('Responsible for making the resource'),
  );

  $form['add']['dc']['publisher'] = array(
    '#type' => 'textfield',
    '#title' => t('Publisher'),
    '#required' => FALSE,
    '#description' => t('Responsible for making the resource available'),
  );

  $form['add']['dc']['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#required' => FALSE,
    '#description' => t('The topic of the resource'),
  );

  // Provide a default date in the format YYYY-MM-DD HH:MM:SS.
  $date = '';

  // Provide a format using regular PHP format parts (see documentation on php.net).
  // If you're using a date_select, the format will control the order of the date parts in the selector,
  // rearrange them any way you like. Parts left out of the format will not be displayed to the user.
  $format = 'Y-m-d';

  $form['add']['dc']['date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Date'),
    '#description' => t('Date of the resource'),
    '#required' => FALSE,
    '#default_value' => $date,
    '#date_format' => $format,
    '#size' => 40,
    '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc

  );

  $form['add']['dc']['identifier'] = array(
    '#type' => 'textfield',
    '#title' => t('Indentifier'),
    '#required' => FALSE,
    '#description' => t('An unambiguous reference to the resource within a given context'),
  );

  $form['add']['dc']['source'] = array(
    '#type' => 'textfield',
    '#title' => t('Source'),
    '#required' => FALSE,
    '#description' => t('A related resource from which the described resource is derived'),
  );

  $form['add']['dc']['relation'] = array(
    '#type' => 'textfield',
    '#title' => t('Relation'),
    '#required' => FALSE,
    '#description' => t('A related resource from which the described resource is derived'),
  );

  $form['add']['dc']['coverage_temporal'] = array(
    '#type' => 'textfield',
    '#title' => t('Temporal coverage'),
    '#required' => FALSE,
    '#description' => t('The spatial or temporal topic of the resource, the spatial applicability of the resource, or the jurisdiction under which the resource is relevant'),
  );

  $form['add']['dc']['coverage_spatial'] = array(
    '#type' => 'textfield',
    '#title' => t('Spatial coverage'),
    '#required' => FALSE,
    '#description' => t('The spatial or temporal topic of the resource, the spatial applicability of the resource, or the jurisdiction under which the resource is relevant'),
  );

  $form['add']['dc']['rights'] = array(
    '#type' => 'textfield',
    '#title' => t('Rights'),
    '#required' => FALSE,
    '#description' => t('Information about rights held in and over the resource.'),
  );

  $form['add']['qdc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Qualified Dublin core'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['add']['qdc']['title_alternative'] = array(
    '#type' => 'textfield',
    '#title' => t('Alternative title'),
    '#required' => FALSE,
    '#description' => t('Alternative title of the resource'),
  );

  $form['add']['qdc']['description_abstra'] = array(
    '#type' => 'textarea',
    '#title' => t('Abstract description'),
    '#required' => FALSE,
    '#rows' => 5,
    '#description' => t('An abstract description of the resource'),
  );

  $form['add']['qdc']['created'] = array(
    '#type' => 'date_popup',
    '#title' => t('Created'),
    '#description' => t('Date of creation of the resource.'),
    '#required' => FALSE,
    '#default_value' => $date,
    '#date_format' => $format,
    '#size' => 40,
    '#date_label_position' => 'within',
  );

  $form['add']['qdc']['issued'] = array(
    '#type' => 'date_popup',
    '#title' => t('Issued'),
    '#description' => t('Date of formal issuance (e.g., publication) of the resource'),
    '#required' => FALSE,
    '#default_value' => $date,
    '#date_format' => $format,
    '#size' => 40,
    '#date_label_position' => 'within',
  );

  $form['add']['qdc']['hasformat'] = array(
    '#type' => 'textfield',
    '#title' => t('Has format'),
    '#required' => FALSE,
    '#description' => t('The described resource pre-existed the referenced resource'),
  );

  $form['add']['qdc']['isformat'] = array(
    '#type' => 'textfield',
    '#title' => t('Is format of'),
    '#required' => FALSE,
    '#description' => t('The described resource is the same intellectual content of the referenced resource, but presented in another format'),
  );

  $form['add']['qdc']['format_medium'] = array(
    '#type' => 'textfield',
    '#title' => t('Medium'),
    '#required' => FALSE,
    '#description' => t('The material or physical carrier of the resource'),
  );

  $form['add']['qdc']['format_extent'] = array(
    '#type' => 'textfield',
    '#title' => t('Extent'),
    '#required' => FALSE,
    '#description' => t('The size or duration of the resource'),
  );

  $form['add']['qdc']['license'] = array(
    '#type' => 'textfield',
    '#title' => t('License'),
    '#required' => FALSE,
    '#description' => t('License of the resource'),
  );

  $form['add']['qdc']['rightsholder'] = array(
    '#type' => 'textfield',
    '#title' => t('Rights'),
    '#required' => FALSE,
    '#description' => t('Rights holder of the resource'),
  );

  $form['add']['qdc']['isreferencedby'] = array(
    '#type' => 'textfield',
    '#title' => t('Is referenced by'),
    '#required' => FALSE,
    '#description' => t('The described resource is referenced, cited, or otherwise pointed to by the referenced resource.'),
  );

  return $form;
}

/**
 * Validation for metadata form.
 */
function mediamosa_sb_asset_upload_step_metadata_form_validate($form, $form_state) {
}

/**
 * Returns form elements for the 'other info' page of the steps. This is the
 * thid and last step of the example steps.
 *
 * @ingroup upload_form
 */
function mediamosa_sb_asset_upload_step_access_form($form, $form_state) {
  $form = array();

  $form['visibility'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility'),
  );

  $form['visibility']['title'] = array(
    '#prefix' => t('Visible in lists'),
    '#type' => 'checkbox',
    '#title' => t('Visible in lists'),
    '#required' => FALSE,
  );

  $form['control'] = array(
    '#type' => 'fieldset',
    '#title' => t('Access control'),
  );

  $form['control']['domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain'),
    '#required' => FALSE,
    '#description' => t('Define which domains can view this video'),
  );

  $form['control']['realm'] = array(
    '#type' => 'textfield',
    '#title' => t('By realm'),
    '#required' => FALSE,
    '#description' => t('Select wich registered users based on there email domain have access to this video'),
  );

  $form['control']['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('By email'),
    '#required' => FALSE,
    '#description' => t('Select wich registered users based on there email adress have access to this video'),
  );

  return $form;
}

/**
 * Returns form elements for the 'other info' page of the steps. This is the
 * thid and last step of the example steps.
 *
 * @ingroup upload_form
 */
function mediamosa_sb_asset_upload_step_transcode_form($form, &$form_state) {
  $form = array();

  $form['transcode'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility'),
  );

  try {
    $profiles = MediaMosaCkConnectorTranscodeWrapper::request_get_transcode_profiles();
  }
  catch (Exception $e) {
    drupal_set_message(t('Unable to retrieve transcode profiles, check MediaMosa Connector.'), 'error');
    return $form;
  }

  $options = array();

  $transcode_profile_default = 0;
  if (!empty($profiles->xml->items->item)) {
    foreach ($profiles->xml->items->item as $profile) {
      $profile_id = (int) $profile->profile_id;

      // Is default profile?
      $options[$profile_id]['is_default'] = drupal_strtoupper((string) $profile->default) == 'TRUE';

      $options[$profile_id]['active'] = FALSE;
      $options[$profile_id]['downloadable'] = FALSE;
      $options[$profile_id]['title'] = (string) $profile->profile;
      $options[$profile_id]['profile_id'] = (int) $profile->profile_id;
    }
  }

  $form['transcode']['table'] = array(
    '#theme' => 'mediamosa_sb_profile_select',
    '#options' => $options, //mediamosa_connector::variable_get('media_mediamosa_transcode_profile_default_options_value', $options),
    '#default_value' => reset($options),
  );

  $form['still'] = array(
    '#type' => 'fieldset',
    '#title' => t('Still generation for this video'),
  );

  $form['still']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Time for still generation'),
    '#required' => FALSE,
    '#size' => 5,
    '#value' => '00.00', // added default value.
    '#description' => t('Enter the time for the frame on which the still wil be generated'),
  );

  return $form;
}

/**
 * Validation for metadata form.
 */
function _mediamosa_sb_asset_upload_steps_finish_validation($form, &$form_state) {
}

/**
 * Wizard form submit handler.
 * - Saves away $form_state['values']
 * - Process all the form values.
 *
 * This demonstration handler just do a drupal_set_message() with the information
 * collected on each different step of the steps.
 *
 * @param $form
 * @param $form_state
 *
 * @ingroup upload_form
 */
function _mediamosa_sb_asset_upload_steps_finish_submit($form, &$form_state) {
  // Store the last step.
  $form_state['step_information'][$form_state['step']]['stored_values'] = $form_state['values'];

  // Run function for posting metadata to MediaMosa.
  mediamosa_sb::post_metadata($form_state['step_information'][1]['stored_values'], $form_state['asset_id'], $form_state['mediafile_id']);

  // Run function for posting access rules to MediaMosa.
  mediamosa_sb::post_access($form_state['step_information'][2]['stored_values'], $form_state['asset_id'], $form_state['mediafile_id']);

  // Run function for posting transcode jobs to MediaMosa.
  mediamosa_sb::post_transcode($form_state['step_information'][3]['stored_values'], $form_state['asset_id'], $form_state['mediafile_id']);

  // Go to view page.
  drupal_goto('asset/' . rawurlencode( $form_state['asset_id']));
}
