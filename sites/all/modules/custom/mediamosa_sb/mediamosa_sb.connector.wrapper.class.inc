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
 * Our connector class.
 */
class MediaMosaSbConnectorWrapper extends MediaMosaCkConnectorWrapper {

  /**
   * Get the asset.
   *
   * @see MediaMosaCkConnectorWrapper::get_asset()
   */
  static public function get_asset($asset_id, array $options = array(), $cached = TRUE, $reset = FALSE) {
    try {
      return parent::get_asset($asset_id, $options, $cached, $reset);
    }
    catch(Exception $e) {
      return FALSE;
    }
  }

  /**
   * Return with array of the users collection.
   *
   * @todo:
   *   Limit is 200.
   */
  static public function get_my_collections_for_options() {
    // Get the user ID.
    $user_id = mediamosa_ck::session_user_id();

    $options = array(
      'offset' => 0,
      'limit' => 200, // Get max allowed per rest call.
      'cql' => strtr('owner_id == "^!user_id^"', array('!user_id' => $user_id)),
    );

    // Get it.
    $collections = array();
    $xml = parent::search_collection($options);
    if ($xml) {
      foreach ($xml->xpath('items/item') as $collection) {
        $collections[(string) $collection->coll_id] = (string) $collection->title;
      }
    }

    return $collections;
  }

  /**
   * Get the access of a mediafile.
   *
   * @see MediaMosaCkConnectorWrapper::get_access_control()
   */
  static public function get_access_control($mediafile_id, $user_id) {
    // Access array.
    $access = array(
      'acl_domain' => array(),
      'acl_realm' => array(),
      'acl_user' => array(),
    );

    // Get access.
    $xml = parent::get_access_control($mediafile_id, $user_id);

    if ($xml) {
      foreach ($xml->xpath('items/item/acl_domain') as $item) {
        $access['acl_domain'][] = (string) $item;
      }
      foreach ($xml->xpath('items/item/acl_realm') as $item) {
        $access['acl_realm'][] = (string) $item;
      }
      foreach ($xml->xpath('items/item/acl_user') as $item) {
        $access['acl_user'][] = (string) $item;
      }
    }

    return $access;
  }
}
