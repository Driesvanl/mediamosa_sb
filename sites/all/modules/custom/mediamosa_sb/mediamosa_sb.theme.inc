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
 * @param type $variables
 * @return type
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

  if (!empty($element['#options'])) {
    foreach ($element['#options'] as $option) {
      $row = array();

      // Checkbox select transcode.
      $checkbox = array(
        '#name' => 'active_' . $option['profile_id'],
        '#type' => 'checkbox',
        '#checked' => $option['active'],
      );

      if (empty($option['is_allowed'])) {
        // #disabled does not seem to work with drupal_render.
        $checkbox['#attributes'] = array('disabled' => 'true');
      }

      $row[] = array('data' => drupal_render($checkbox));

      // Title.
      $row[] = array('data' => check_plain($option['title']));

      // Checkbox select transcode.
      $checkbox = array(
        '#id' => 'downloadable_' . $option['profile_id'],
        '#name' => 'downloadable_' . $option['profile_id'],
        '#type' => 'checkbox',
        '#checked' => $option['active'],
        '#states' => array(
          // Hide the settings when the cancel notify checkbox is disabled.
          'invisible' => array(
            'input[name="active_' . $option['profile_id'] . '"]' => array('checked' =>FALSE),
          ),
        ),
      );
      $row[] = array('data' => drupal_render($checkbox));

      $rows[] = $row;
    }
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => $element['#empty'], 'attributes' => $element['#attributes']));
}
