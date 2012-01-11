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
 * @file
 * Simple static class to hold form functions, so we keep our inc files cleaner
 * and this is autoloaded.
 */
class mediamosa_sb_asset_forms {
  // ---------------------------------------------------------------- Functions.
  /**
   * Return the default value.
   */
  static protected function default_value($values, $name) {
    return empty($values[$name]) ? '' : $values[$name];
  }

  /**
   * The metadata form.
   *
   * @param $form_state
   *   The form state array.
   *
   * @return
   *   Returns the form array.
   */
  static public function metadata_form($values) {
    $form = array();

    // Get the collections.
    $options_collections = MediaMosaSbConnectorWrapper::get_my_collections_for_options();

    $form['basic'] = array(
      '#type' => 'fieldset',
      '#title' => t('Basic Information'),
    );

    // dc.title is translated by Drupal to dc_title in form_state['input'],
    // so better use _ instead from the start.
    $form['basic']['dc_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#required' => TRUE,
      '#default_value' => self::default_value($values, 'dc_title'),
    );

    $form['basic']['dc_description'] = array(
      '#type' => 'textfield',
      '#title' => t('Description'),
      '#required' => FALSE,
      '#default_value' => self::default_value($values, 'dc_description'),
    );

    $form['collections'] = array(
      '#type' => 'fieldset',
      '#title' => t('Collections'),
    );

    $form['collections']['mycollections'] = array(
      '#type' => 'select',
      '#title' => t('My collections'),
      '#required' => FALSE,
      '#size'=> 5,
      '#options' => $options_collections,
      '#default_value' => self::default_value($values, 'mycollections'),
    );

    $form['additional'] = array(
      '#type' => 'fieldset',
      '#title' => t('Additional metadata <span>(According Dublin Metadata Initiative)</span>'),
    );

    $form['additional']['dc'] = array(
      '#type' => 'fieldset',
      '#title' => t('Dublin core'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['additional']['dc']['dc_type'] = array(
      '#type' => 'textfield',
      '#title' => t('Type'),
      '#required' => FALSE,
      '#description' => t('The nature or genre of the resource e.g. Image, MovingImage'),
      '#default_value' => self::default_value($values, 'dc_type'),
    );

    $form['additional']['dc']['dc_format'] = array(
      '#type' => 'textfield',
      '#title' => t('Format'),
      '#required' => FALSE,
      '#description' => t('The file format, physical medium e.g. video, image'),
      '#default_value' => self::default_value($values, 'dc_format'),
    );

    $form['additional']['dc']['dc_language'] = array(
      '#type' => 'select',
      '#title' => t('Language'),
      '#required' => FALSE,
      '#description' => t('The language of the resource'),
      '#options'  => mediamosa_sb::get_metdata_languages_options(),
      '#default_value' => self::default_value($values, 'dc_language'),
    );

    $form['additional']['dc']['dc_creator'] = array(
      '#type' => 'textfield',
      '#title' => t('Creator'),
      '#required' => FALSE,
      '#description' => t('Responsible for making the resource'),
      '#default_value' => self::default_value($values, 'dc_creator'),
    );

    $form['additional']['dc']['dc_publisher'] = array(
      '#type' => 'textfield',
      '#title' => t('Publisher'),
      '#required' => FALSE,
      '#description' => t('Responsible for making the resource available'),
      '#default_value' => self::default_value($values, 'dc_publisher'),
    );

    $form['additional']['dc']['dc_subject'] = array(
      '#type' => 'textfield',
      '#title' => t('Subject'),
      '#required' => FALSE,
      '#description' => t('The topic of the resource'),
      '#default_value' => self::default_value($values, 'dc_subject'),
    );

    // Provide a default date in the format YYYY-MM-DD HH:MM:SS.
    $date = '';

    // Provide a format using regular PHP format parts (see documentation on php.net).
    // If you're using a date_select, the format will control the order of the date parts in the selector,
    // rearrange them any way you like. Parts left out of the format will not be displayed to the user.
    $format = 'Y-m-d';

    $form['additional']['dc']['dc_date'] = array(
      '#type' => 'date_popup',
      '#title' => t('Date'),
      '#description' => t('Date of the resource'),
      '#required' => FALSE,
      '#default_value' => $date,
      '#date_format' => $format,
      '#size' => 40,
      '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
      '#default_value' => self::default_value($values, 'dc_date'),
    );

    $form['additional']['dc']['dc_identifier'] = array(
      '#type' => 'textfield',
      '#title' => t('Indentifier'),
      '#required' => FALSE,
      '#description' => t('An unambiguous reference to the resource within a given context'),
      '#default_value' => self::default_value($values, 'dc_identifier'),
    );

    $form['additional']['dc']['dc_source'] = array(
      '#type' => 'textfield',
      '#title' => t('Source'),
      '#required' => FALSE,
      '#description' => t('A related resource from which the described resource is derived'),
      '#default_value' => self::default_value($values, 'dc_source'),
    );

    $form['additional']['dc']['dc_relation'] = array(
      '#type' => 'textfield',
      '#title' => t('Relation'),
      '#required' => FALSE,
      '#description' => t('A related resource from which the described resource is derived'),
      '#default_value' => self::default_value($values, 'dc_relation'),
    );

    $form['additional']['dc']['dc_coverage_temporal'] = array(
      '#type' => 'textfield',
      '#title' => t('Temporal coverage'),
      '#required' => FALSE,
      '#description' => t('The spatial or temporal topic of the resource, the spatial applicability of the resource, or the jurisdiction under which the resource is relevant'),
      '#default_value' => self::default_value($values, 'dc_coverage_temporal'),
    );

    $form['additional']['dc']['dc_coverage_spatial'] = array(
      '#type' => 'textfield',
      '#title' => t('Spatial coverage'),
      '#required' => FALSE,
      '#description' => t('The spatial or temporal topic of the resource, the spatial applicability of the resource, or the jurisdiction under which the resource is relevant'),
      '#default_value' => self::default_value($values, 'dc_coverage_spatial'),
    );

    $form['additional']['dc']['dc_rights'] = array(
      '#type' => 'textfield',
      '#title' => t('Rights'),
      '#required' => FALSE,
      '#description' => t('Information about rights held in and over the resource.'),
      '#default_value' => self::default_value($values, 'dc_rights'),
    );

    $form['additional']['qdc'] = array(
      '#type' => 'fieldset',
      '#title' => t('Qualified Dublin core'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['additional']['qdc']['qdc_title_alternative'] = array(
      '#type' => 'textfield',
      '#title' => t('Alternative title'),
      '#required' => FALSE,
      '#description' => t('Alternative title of the resource'),
      '#default_value' => self::default_value($values, 'qdc_title_alternative'),
    );

    $form['additional']['qdc']['qdc_description_abstract'] = array(
      '#type' => 'textarea',
      '#title' => t('Abstract description'),
      '#required' => FALSE,
      '#rows' => 5,
      '#description' => t('An abstract description of the resource'),
      '#default_value' => self::default_value($values, 'qdc_description_abstract'),
    );

    $form['additional']['qdc']['qdc_created'] = array(
      '#type' => 'date_popup',
      '#title' => t('Created'),
      '#description' => t('Date of creation of the resource.'),
      '#required' => FALSE,
      '#default_value' => $date,
      '#date_format' => $format,
      '#size' => 40,
      '#date_label_position' => 'within',
      '#default_value' => self::default_value($values, 'qdc_created'),
    );

    $form['additional']['qdc']['qdc_issued'] = array(
      '#type' => 'date_popup',
      '#title' => t('Issued'),
      '#description' => t('Date of formal issuance (e.g., publication) of the resource'),
      '#required' => FALSE,
      '#default_value' => $date,
      '#date_format' => $format,
      '#size' => 40,
      '#date_label_position' => 'within',
      '#default_value' => self::default_value($values, 'qdc_issued'),
    );

    $form['additional']['qdc']['qdc_hasformat'] = array(
      '#type' => 'textfield',
      '#title' => t('Has format'),
      '#required' => FALSE,
      '#description' => t('The described resource pre-existed the referenced resource'),
      '#default_value' => self::default_value($values, 'qdc_hasformat'),
    );

    $form['additional']['qdc']['qdc_isformat'] = array(
      '#type' => 'textfield',
      '#title' => t('Is format of'),
      '#required' => FALSE,
      '#description' => t('The described resource is the same intellectual content of the referenced resource, but presented in another format'),
      '#default_value' => self::default_value($values, 'qdc_isformat'),
    );

    $form['additional']['qdc']['qdc_format_medium'] = array(
      '#type' => 'textfield',
      '#title' => t('Medium'),
      '#required' => FALSE,
      '#description' => t('The material or physical carrier of the resource'),
      '#default_value' => self::default_value($values, 'qdc_format_medium'),
    );

    $form['additional']['qdc']['qdc_format_extent'] = array(
      '#type' => 'textfield',
      '#title' => t('Extent'),
      '#required' => FALSE,
      '#description' => t('The size or duration of the resource'),
      '#default_value' => self::default_value($values, 'qdc_format_extent'),
    );

    $form['additional']['qdc']['qdc_license'] = array(
      '#type' => 'textfield',
      '#title' => t('License'),
      '#required' => FALSE,
      '#description' => t('License of the resource'),
      '#default_value' => self::default_value($values, 'qdc_license'),
    );

    $form['additional']['qdc']['qdc_rightsholder'] = array(
      '#type' => 'textfield',
      '#title' => t('Rights'),
      '#required' => FALSE,
      '#description' => t('Rights holder of the resource'),
      '#default_value' => self::default_value($values, 'qdc_rightsholder'),
    );

    $form['additional']['qdc']['qdc_isreferencedby'] = array(
      '#type' => 'textfield',
      '#title' => t('Is referenced by'),
      '#required' => FALSE,
      '#description' => t('The described resource is referenced, cited, or otherwise pointed to by the referenced resource.'),
      '#default_value' => self::default_value($values, 'qdc_isreferencedby'),
    );

    return $form;
  }

  /**
   * The access form.
   *
   * @param $form_state
   *   The form state array.
   *
   * @return
   *   Returns the form array.
   */
  static public function access_form($values) {
    $form = array();

    $form['visibility'] = array(
      '#type' => 'fieldset',
      '#title' => t('Visibility'),
    );

    // is_visible = !isprivate
    $form['visibility']['is_visible'] = array(
      '#prefix' => t('Visible in lists'),
      '#type' => 'checkbox',
      '#title' => t('Visible in lists'),
      '#required' => FALSE,
      '#default_value' => self::default_value($values, 'is_visible'),
    );

    $form['control'] = array(
      '#type' => 'fieldset',
      '#title' => t('Access control'),
    );

    $form['control']['acl_domain'] = array(
      '#type' => 'textfield',
      '#title' => t('Domain'),
      '#required' => FALSE,
      '#description' => t('Define which domains can view this video. Example; uu.nl, example.com'),
      '#default_value' => self::default_value($values, 'acl_domain'),
    );

    $form['control']['acl_realm'] = array(
      '#type' => 'textfield',
      '#title' => t('By realm'),
      '#required' => FALSE,
      '#description' => t('Select wich registered users based on their email domain have access to this video. Example; @uu.nl, @example.com'),
      '#default_value' => self::default_value($values, 'acl_realm'),
    );

    $form['control']['acl_user'] = array(
      '#type' => 'textfield',
      '#title' => t('By email'),
      '#required' => FALSE,
      '#description' => t('Select wich registered users based on their email adress have access to this video. Example; naam@uu.nl, name@example.com'),
      '#default_value' => self::default_value($values, 'acl_user'),
    );

    return $form;
  }

  /**
   * The transcode/still form.
   *
   * @param $form_state
   *   The form state array.
   *
   * @return
   *   Returns the form array.
   */
  static public function media_form($values) {
    $form = array();

    // The asset ID.
    $asset_id = $values['asset_id'];

    $form['transcode'] = array(
      '#type' => 'fieldset',
      '#title' => t('Visibility'),
    );

    $xml = MediaMosaCkConnectorWrapper::get_transcode_profiles();
    if ($xml == FALSE) {
      drupal_set_message(t('Unable to retrieve transcode profiles, check MediaMosa Connector.'), 'error');
    }

    $options = array();

    // Get the allowed profiles.
    $allowed_profiles = MediaMosaCkConnectorWrapper::get_allowed_transcode_profiles();

    // List of the profile IDs that are used.
    $existing_transcodes = array();
    $is_downloadable = array();

    // Get the default profiles, these can not be deleted or recreated.
    $default_profile = MediaMosaCkConnectorWrapper::get_default_transcode_profile();

    try {
      // Get existing mediafiles.
      $asset = MediaMosaCkConnectorWrapper::get_asset($asset_id);

      // Loop through the mediafiles.
      foreach ($asset->xpath('items/item/mediafiles/mediafile') as $mediafile) {
        // Skip original.
        if (MediaMosaCkConnectorWrapper::string2bool($mediafile->is_original_file)) {
          continue;
        }

        // Collect the transcodes.
        if (!empty($mediafile->transcode_profile_id)) {
          $existing_transcodes[$mediafile->transcode_profile_id] = $mediafile->transcode_profile_id;
        }

        // Collect the downloadables.
        if (MediaMosaCkConnectorWrapper::string2bool($mediafile->is_downloadable)) {
          $is_downloadable[$mediafile->transcode_profile_id] = $mediafile->transcode_profile_id;
        }
      }
    }
    catch (Exception $e) {
      mediamosa_ck::watchdog_error('Unable to find existing mediafiles.');
    }

    $transcode_profile_default = 0;
    if (!empty($xml->items->item)) {
      foreach ($xml->items->item as $profile) {
        $profile_id = (int) $profile->profile_id;

        // Is allowed as profile? If a mediafile exists, we ignore the allowed profile.
        if (!isset($allowed_profiles[$profile_id]) && !isset($existing_transcodes[$profile_id])) {
          continue;
        }

        // Exists as transcode?
        $active = isset($existing_transcodes[$profile_id]);

        // Is default profile?
        $options[$profile_id]['is_default'] = $profile_id == $default_profile;
        $options[$profile_id]['is_allowed'] = $profile_id != $default_profile;

        $options[$profile_id]['active'] = $active;
        $options[$profile_id]['downloadable'] = FALSE;
        $options[$profile_id]['title'] = (string) $profile->profile;
        $options[$profile_id]['profile_id'] = (int) $profile->profile_id;
      }
    }

    $form['transcode']['table'] = array(
      '#theme' => 'mediamosa_sb_profile_select',
      '#options' => $options,
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
}
