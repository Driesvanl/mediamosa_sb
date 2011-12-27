<?php
/**
 * MediaMosa is a Full Featured, Webservice Oriented Media Management and
 * Distribution platform (http://www.vpcore.nl)
 *
 * Copyright (C) 2011 SURFnet BV (http://www.surfnet.nl)
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
 * The plugin query object for MediaMosa allows REST calls inside views. It
 * uses the Views 3 plugin option to query another source instead of the normal
 * Drupal database.
 *
 * View is based on the REST call 'asset'.
 *
 */
class mediamosa_ck_views_rest_asset_search extends mediamosa_ck_views_rest {

  /**
   * Execute the REST call.
   *
   * @param $view
   *   The view object.
   * @param $params
   *   Array of options and settings.
   */
  protected function do_rest_call($view, $params, array $options = array()) {
    $options += array(
      'offset' => $params['start'],
      'limit' => $params['rows'],
      'hide_empty_assets' => 'TRUE',
    );

    // Do the search.
    $response = MediaMosaCkConnectorWrapper::request_asset_search($options);

    $fields = array(
      'viewed', 'played',
      'videotimestamp', 'videotimestampmodified',
    );

    // Now process the xml into an object views can work with.
    foreach($response->xml->xpath('items/item') as $item) {
      $object = new stdClass();
      $object->asset_id = (string) $item->asset_id;
      $object->granted = drupal_strtoupper((string) $item->granted) == 'TRUE' ? 'TRUE' : 'FALSE';

      foreach (mediamosa_ck::get_metadata_fields() as $set => $metadata) {
        foreach ($item->xpath($metadata['xpath']) as $metadata_value) {
          foreach ($metadata_value as $name => $value) {
            $object->{$set . '.' . (string) $name} = (string) $value;
          }
        }
      }

      // Fill the array.
      foreach ($fields as $field) {
        // @todo need to get default value when value is empty.
        $object->{$field} = isset($item->{$field}) ? (string) $item->{$field} : '';
      }

      // The name of the field to use.
      $title_name = mediamosa_ck::get_metadata_title();

      // @todo need to get default value when title is empty.
      $object->title = $object->{$title_name};

      $view->result[] = $object;
    }

    // Assign total number of records to get pager.
    $view->total_rows = (int) $response->xml->header->item_count_total;
  }

  /**
   * Get the views data for this REST call.
   *
   * @return
   */
  static public function get_views_data($title, $class) {
    $data = array(
      'table' => array(
        'group' => t('MediaMosa'),
        'base' => array(
          'field' => 'id',
          'title' => t($title),
          'help' => t('Retrieve and search assets in the MediaMosa backend'),
          'query class' => $class,
        ),
      ),

      // Fields.
      'asset_id' => array(
        'title' => t('Asset ID'),
        'help' => t('Unique Identifier of each asset.'),
        'field' => array(
          'handler' => 'mediamosa_ck_views_field_text',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'mediamosa_ck_views_filter_text',
          'mediamosa_filter_keys' => array('filter_key' => 'granted'),
        ),
        'sort' => array(
          'handler' => 'mediamosa_ck_views_sort',
        ),
      ),

      'granted' => array(
        'title' => t('Granted'),
        'help' => t('Granted value indicates if you are allowed to see and play mediafile.'),
        'field' => array(
          'handler' => 'mediamosa_ck_views_field_text',
        ),
        'filter' => array(
          'handler' => 'mediamosa_ck_views_filter_text',
        ),
      ),

      'viewed' => array(
        'title' => t('Viewed'),
        'help' => t('Number of times viewed.'),
        'field' => array(
          'handler' => 'mediamosa_ck_views_field_text',
          'click sortable' => TRUE,
        ),
        'sort' => array(
          'handler' => 'mediamosa_ck_views_sort',
        ),
      ),

      'played' => array(
        'title' => t('Played'),
        'help' => t('Number of times played.'),
        'field' => array(
          'handler' => 'mediamosa_ck_views_field_text',
          'click sortable' => TRUE,
        ),
        'sort' => array(
          'handler' => 'mediamosa_ck_views_sort',
        ),
      ),

      'videotimestamp' => array(
        'title' => t('Videotimestamp'),
        'help' => t('When asset got a video.'),
        'field' => array(
          'handler' => 'mediamosa_ck_views_field_date',
        ),
        'sort' => array(
          'handler' => 'mediamosa_ck_views_sort',
        ),
      ),

      'videotimestampmodified' => array(
        'title' => t('Videotimestamp modified'),
        'help' => t('When asset was modified.'),
        'field' => array(
          'handler' => 'mediamosa_ck_views_field_date',
        ),
        'sort' => array(
          'handler' => 'mediamosa_ck_views_sort',
        ),
      ),

      // Fields.
      'title' => array(
        'title' => t('Title'),
        'help' => t('The title of the asset. Is for display purpose only.'),
        'field' => array(
          'handler' => 'mediamosa_ck_views_field_text',
          'click sortable' => FALSE,
        ),
      ),

      'still_url' => array(
        'title' => t('Still'),
        'help' => t('The thumbnail of the media.'),
        'field' => array(
          'handler' => 'mediamosa_ck_views_field_still',
        ),
      ),
    );

    // Add metadata.
    foreach (mediamosa_ck::get_metadata_fields() as $set => $metadata) {
      foreach ($metadata['fields'] as $name => $type) {

        //
        switch ($type) {
          case 'DATETIME':
            $data[$set . '_' . $name] = array(
              'title' => t($set . '.' . $name),
              'help' => t('Metadata date field in @set_label.', array('@set_label' => $metadata['title'])),
              'field' => array(
                'handler' => 'mediamosa_ck_views_field_date',
                'click sortable' => TRUE,
              ),
              'sort' => array(
                'handler' => 'mediamosa_ck_views_sort',
              ),
            );
            break;

          case 'CHAR':
          case 'INT':
          default:
            $data[$set . '_' . $name] = array(
              'title' => t($set . '.' . $name),
              'help' => t('Metadata field in @set_label.', array('@set_label' => $metadata['title'])),
              'field' => array(
                'handler' => 'mediamosa_ck_views_field_text',
                'click sortable' => TRUE,
              ),
              'filter' => array(
                'handler' => 'mediamosa_ck_views_filter_text',
              ),
              'sort' => array(
                'handler' => 'mediamosa_ck_views_sort',
              ),
            );
            break;
        }
      }
    }

    return $data;
  }
}
