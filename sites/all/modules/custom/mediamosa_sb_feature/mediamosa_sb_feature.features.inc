<?php
/**
 * @file
 * mediamosa_sb_feature.features.inc
 */

/**
 * Implements hook_views_api().
 */
function mediamosa_sb_feature_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}
