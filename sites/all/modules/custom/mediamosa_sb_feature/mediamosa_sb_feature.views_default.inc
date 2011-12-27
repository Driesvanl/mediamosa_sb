<?php
/**
 * @file
 * mediamosa_sb_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function mediamosa_sb_feature_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'mediamosa_asset_featured';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'mediamosa_asset_featured';
  $view->human_name = 'MediaMosa Asset Featured';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'MediaMosa Asset Featured';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['group_rendered'] = 1;
  $handler->display->display_options['style_options']['columns'] = '3';
  $handler->display->display_options['style_options']['fill_single_line'] = 1;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: MediaMosa: Asset ID */
  $handler->display->display_options['fields']['asset_id']['id'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['asset_id']['field'] = 'asset_id';
  $handler->display->display_options['fields']['asset_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['asset_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['asset_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['asset_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['asset_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['asset_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['asset_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['asset_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['asset_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['asset_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['asset_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['asset_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['asset_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['asset_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['asset_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['asset_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['asset_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['asset_id']['hide_alter_empty'] = 1;
  /* Field: MediaMosa: Granted */
  $handler->display->display_options['fields']['granted']['id'] = 'granted';
  $handler->display->display_options['fields']['granted']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['granted']['field'] = 'granted';
  $handler->display->display_options['fields']['granted']['exclude'] = TRUE;
  $handler->display->display_options['fields']['granted']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['external'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['granted']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['granted']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['granted']['alter']['html'] = 0;
  $handler->display->display_options['fields']['granted']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['granted']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['granted']['hide_empty'] = 0;
  $handler->display->display_options['fields']['granted']['empty_zero'] = 0;
  $handler->display->display_options['fields']['granted']['hide_alter_empty'] = 1;
  /* Field: MediaMosa: Still */
  $handler->display->display_options['fields']['still_url']['id'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['still_url']['field'] = 'still_url';
  $handler->display->display_options['fields']['still_url']['label'] = '';
  $handler->display->display_options['fields']['still_url']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['still_url']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['still_url']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['still_url']['alter']['external'] = 0;
  $handler->display->display_options['fields']['still_url']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['still_url']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['still_url']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['still_url']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['still_url']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['still_url']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['still_url']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['still_url']['alter']['html'] = 0;
  $handler->display->display_options['fields']['still_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['still_url']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['still_url']['hide_empty'] = 0;
  $handler->display->display_options['fields']['still_url']['empty_zero'] = 0;
  $handler->display->display_options['fields']['still_url']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['still_url']['still_style'] = 'thumbnail';
  /* Field: MediaMosa: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['empty'] = 'No title available';
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  /* Field: MediaMosa: Played */
  $handler->display->display_options['fields']['played']['id'] = 'played';
  $handler->display->display_options['fields']['played']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['played']['field'] = 'played';
  $handler->display->display_options['fields']['played']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['played']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['played']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['played']['alter']['external'] = 0;
  $handler->display->display_options['fields']['played']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['played']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['played']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['played']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['played']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['played']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['played']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['played']['alter']['html'] = 0;
  $handler->display->display_options['fields']['played']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['played']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['played']['hide_empty'] = 0;
  $handler->display->display_options['fields']['played']['empty_zero'] = 0;
  $handler->display->display_options['fields']['played']['hide_alter_empty'] = 1;
  /* Field: MediaMosa: Videotimestamp */
  $handler->display->display_options['fields']['videotimestamp']['id'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['videotimestamp']['field'] = 'videotimestamp';
  $handler->display->display_options['fields']['videotimestamp']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['alter']['external'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['videotimestamp']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['videotimestamp']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['alter']['html'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['videotimestamp']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['videotimestamp']['hide_empty'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['empty_zero'] = 0;
  $handler->display->display_options['fields']['videotimestamp']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['videotimestamp']['date_format'] = 'medium';
  /* Field: MediaMosa: Viewed */
  $handler->display->display_options['fields']['viewed']['id'] = 'viewed';
  $handler->display->display_options['fields']['viewed']['table'] = 'mediamosa_asset_featured';
  $handler->display->display_options['fields']['viewed']['field'] = 'viewed';
  $handler->display->display_options['fields']['viewed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['viewed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['viewed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['viewed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['viewed']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['viewed']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['viewed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['viewed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['viewed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['viewed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['viewed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['viewed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['viewed']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['viewed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['viewed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['viewed']['empty_zero'] = 0;
  $handler->display->display_options['fields']['viewed']['hide_alter_empty'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'mediamosa/asset/featured';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $export['mediamosa_asset_featured'] = $view;

  return $export;
}
