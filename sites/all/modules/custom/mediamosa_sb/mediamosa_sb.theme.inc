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
 * All theme (related) functions.
 */

/**
 * Custom theme for profile.
 *
 * @param $variables
 *   Theme variables.
 *
 * @return
 *   The rendered HTML.
 */
function theme_mediamosa_sb_profile_select($variables) {

  // Shortcut to element.
  $element = $variables['element'];

  $element += array(
    '#empty' => t('No transcode profiles found.'),
  );

  $rows = array();
  $header = array(
    'active' => t('Active'),
    'profile' => t('Profile'),
    'downloadable' => t('Downloadable'),
  );

  $extra = array();
  if (!empty($element['#options'])) {
    foreach ($element['#options'] as $option) {
      $row = array();

      // Checkbox select transcode.
      $checkbox = array(
        '#name' => 'active_' . $option['profile_id'],
        '#type' => 'checkbox',
        '#checked' => $option['checked_transcode'],
      );

      // If disabled, we'll store the value of active in a hidden, so this value
      // is submitted.
      if (!empty($option['disabled'])) {
        // Copy into hidden.
        $hidden = $checkbox;
        $hidden['#type'] = 'hidden';
        $hidden['#value'] = $hidden['#checked'];
        unset($hidden['#checked']);
        $extra[] = drupal_render($hidden);

        $checkbox['#name'] = 'disabled_active_' . $option['profile_id'];

        // #disabled does not seem to work with drupal_render.
        $checkbox['#attributes'] = array('disabled' => 'true');
      }
      $row[] = array('data' => drupal_render($checkbox));

      // Title.
      $row[] = array('data' => check_plain($option['title']) . ($option['default'] ? '<br /><small>' . t('(default profile)') . '</small>' : ''));

      // Only when active. This is a hotfix because we can't set downloadable
      // on a transcode that is started. Can only set downloadable when
      // mediafile is present.
      if ($option['checked_transcode']) {
        // Checkbox select downloadable.
        $checkbox = array(
          '#id' => 'downloadable_' . $option['profile_id'],
          '#name' => 'downloadable_' . $option['profile_id'],
          '#type' => 'checkbox',
          '#checked' => $option['checked_downloadable'],
          '#states' => array(
            // Hide the settings when the cancel notify checkbox is disabled.
            'invisible' => array(
              'input[name="active_' . $option['profile_id'] . '"]' => (!empty($option['disabled']) ? array('value' => FALSE) : array('checked' => FALSE)),
            ),
          ),
        );
        $row[] = array('data' => drupal_render($checkbox));
      }
      else {
        $row[] = array('data' => '&nbsp;');
      }

      $rows[] = $row;
    }
  }

  return implode('', $extra) . theme('table', array('header' => $header, 'rows' => $rows, 'empty' => $element['#empty'], 'attributes' => $element['#attributes']));
}
