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
 */
class mediamosa_ck_views_rest_collection_search extends mediamosa_ck_views_rest {

  /**
   * Execute the REST call.
   *
   * @param $view
   *   The view object.
   * @param $params
   *   Array of options and settings.
   */
  public function do_rest_call($view, $params, array $options = array()) {
    $options += array(
      'offset' => $params['start'],
      'limit' => $params['rows'],
    );

    // Do the search.
    $response = MediaMosaCkConnectorWrapper::request_collection_search($options);

    // Now process the xml into an object views can work with.
    foreach($response->xml->xpath('items/item') as $item) {
      $object = new stdClass();
      $object->coll_id = (string) $item->coll_id;
      $object->title = (string) $item->title;
      $object->description = (string) $item->description;
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
    return array(
      'table' => array(
        'group' => t('MediaMosa'),
        'base' => array(
          'field' => 'id',
          'title' => t($title),
          'help' => t('Retrieve and search collections in the MediaMosa backend'),
          'query class' => $class,
        ),
      ),

      // Fields.
      'coll_id' => array(
        'title' => t('Collection ID'),
        'help' => t('Unique Identifier of each collection.'),
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

      'title' => array(
        'title' => t('Title'),
        'help' => t('The title of the collection.'),
        'field' => array(
          'handler' => 'mediamosa_ck_views_field_text',
        ),
        'filter' => array(
          'handler' => 'mediamosa_ck_views_filter_text',
        ),
        'sort' => array(
          'handler' => 'mediamosa_ck_views_sort',
        ),
      ),

      'description' => array(
        'title' => t('Description'),
        'help' => t('The description of the collection.'),
        'field' => array(
          'handler' => 'mediamosa_ck_views_field_text',
        ),
        'filter' => array(
          'handler' => 'mediamosa_ck_views_filter_text',
        ),
        'sort' => array(
          'handler' => 'mediamosa_ck_views_sort',
        ),
      ),
    );
  }
}
