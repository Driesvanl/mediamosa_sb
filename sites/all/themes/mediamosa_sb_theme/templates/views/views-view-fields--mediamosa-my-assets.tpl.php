<?php
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<?php if (isset($fields['still_url']) && !empty($fields['still_url']->content)): ?>
  <?php print $fields['still_url']->content; ?>
<?php endif; ?>

<div class="asset-information">
  <?php print $fields['mediafile_duration']->wrapper_prefix; ?>
  <?php print $fields['mediafile_duration']->content; ?>
  <?php print $fields['mediafile_duration']->wrapper_suffix; ?>

  <?php print $fields['played']->wrapper_prefix; ?>
  <?php print $fields['played']->content; ?>
  <?php print $fields['played']->wrapper_suffix; ?>

  <?php print $fields['title']->wrapper_prefix; ?>
  <?php print $fields['title']->content; ?>
  <?php print $fields['title']->wrapper_suffix; ?>

  <?php print $fields['videotimestamp']->wrapper_prefix; ?>
  <?php print $fields['videotimestamp']->content; ?>
  <?php print $fields['videotimestamp']->wrapper_suffix; ?>
</div>

<?php if (_mediamosa_sb_access_asset_edit($fields['asset_id']->raw)): ?>
  <ul class="asset-options">
    <li><?php print l(t('edit'), 'asset/edit/' . $fields['asset_id']->raw); ?></li>
    <li><?php print l(t('delete'), 'asset/delete/' . $fields['asset_id']->raw); ?></li>
  </ul>
<?php endif; ?>