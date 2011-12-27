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
abstract class mediamosa_ck_views_rest extends views_plugin_query {
  // ---------------------------------------------------------------- Variables.
  var $requests;
  var $aliases;
  var $params;
  var $orderby;
  var $required_fields;

  // ----------------------------------------------------- Functions (abstract).
  // Execute the rest call.
  //abstract protected function do_rest_call($view, $params, array $options = array());
  // Return information for the views_data hook.
 // abstract static public function get_views_data($title, $class);

  // ---------------------------------------------------------------- Functions.
  /**
   * Builds the necessary info to execute the query.
   *
   * @param $view
   *   The view object.
   */
  public function build($view) {
    // Setup the view object.
    $view->init_pager();

    // Let the pager modify the query to add limits.
    $this->pager->query();

    // Set aliases of the fields.
    foreach ($view->field as $field_name => &$field) {
      $field->field_alias = $field_name;
      $field->aliases['entity_type'] = 'entity_type';
    }

    // Add fields to the query so they will be shown in solr document.
    $this->params['fl'] = array_keys($view->field);
  }

  /**
   * Add a field to the query table, possibly with an alias. This will
   * automatically call ensure_table to make sure the required table
   * exists, *unless* $table is unset.
   *
   * @param $table
   *   The table this field is attached to, here it is the ID of the REST view
   *   class.
   * @param $field
   *   The name of the field to add.
   * @param $required
   *   TRUE or FALSE, will add the field to required listing as input.
   *
   * @return $name
   *   The name that this field can be referred to as. Usually this is the
   *   alias.
   */
  public function add_field($table, $field, $required = FALSE) {
    $alias = "{$table}_{$field}";
    $this->aliases[$table][$field] = $alias;

    if ($required) {
      $this->required_fields[$alias] = $alias;
    }

    return $alias;
  }

  /**
   * Executes the query and fills the associated view object with according
   * values.
   *
   * Values to set:
   * $view->result,
   * $view->total_rows,
   * $view->execute_time,
   * $view->pager['current_page'].
   */
  public function execute($view) {
    try {
      $start = microtime(TRUE);

      // Setup the params.
      $params = array();
      $params['rows'] = $this->pager->options['items_per_page'];
      $params['start'] = $this->pager->current_page * $this->pager->options['items_per_page'];

      // Params to copy.
      $param_fields = array(
        'q' => 'q',
        'fl' => 'fl',
        'filters' => 'filters',
        'sort' => 'sort',
      );

      // Copy needed fields.
      foreach ($param_fields as $param_field) {
        if (!empty($this->params[$param_field])) {
          $params[$param_field] = $this->params[$param_field];
        }
      }

      // Perform request to MediaMosa.
      $this->do_rest_call($view, $params);

      // Store the results.
      $this->pager->total_items = $view->total_rows;
      $this->pager->update_page_info();

      // We shouldn't use $results['performance']['complete'] here, since
      // extracting the results probably takes considerable time as well.
      $view->execute_time = microtime(TRUE) - $start;
    }
    catch (Exception $e) {
      $this->errors[] = $e->getMessage();
    }

    // @todo: unsure if we want to use drupal_set_message here.
    if (!empty($this->errors)) {
      foreach ($this->errors as $msg) {
        drupal_set_message($msg, 'error');
      }
      $view->result = array();
      $view->total_rows = 0;
      $view->execute_time = 0;
    }
  }

  public function add_filter($type, $value, $exclude = FALSE) {
    $this->params['filters'][$type] = ($exclude ? '-' : '') . $value;
  }

  public function add_filter_string($string) {
    $this->params['q.alt'][] = $string;
  }

  public function add_sort($field, $order) {
    $this->params['sort'][] = $field . ' ' . $order;
  }

  public function get_params() {
    return $this->params;
  }
}
