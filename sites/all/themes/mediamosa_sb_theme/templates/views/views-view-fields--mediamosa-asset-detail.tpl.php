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
<ul class="item-navigation">
  <li><span><?php print l(t('View'), 'view', array('attributes' => array('class' => 'view'))); ?></span></li>
  <li><span><?php print l(t('Edit'), 'asset/edit/' . $fields['asset_id']->raw, array('attributes' => array('class' => 'edit'))); ?></span></li>
</ul>
<h1><?php print $fields['title']->content; ?></h1>

<div class="asset-video-player">
  <?php print $fields['player']->content; ?>
</div>

<div class="asset-detail-information">
  <div class="information-row">
    <p class="asset-view-count"><span class="count"><?php print $fields['played']->content; ?></span> <?php print t('views'); ?></p>

    <p class="asset-uploaded-info">
      <?php print t('Posted by');?>: <strong><?php print $fields['metadata_dc']->raw['contributor']; ?></strong> <?php print t('on'); ?> <strong><?php print $fields['metadata_dc']->raw['date']; ?></strong>
    </p>
  </div>

  <div class="information-row asset-collections">
    <h3><?php print t('Collections'); ?></h3>

    <p><?php print t('This video is listed in the following Collection(s)'); ?>:</p>

    <ul>
      <li><?php print l('[hardcoded] Farmacologie', 'collection/O1Vb4NCUOolkT7iXSTVZmj0M');?></li>
      <li><?php print l('[hardcoded] Lorem ipsum', 'collection/O1Vb4NCUOolkT7iXSTVZmj0M');?></li>
      <li><?php print l('[hardcoded] Dolor Sit Amet', 'collection/O1Vb4NCUOolkT7iXSTVZmj0M');?></li>
    </ul>
  </div>

  <div class="information-row asset-formats">
    <h3><?php print t('Additional format(s)'); ?></h3>

    <p><?php print t('This video is available in the following additional format(s)'); ?>:</p>

    <ul>
      <li><?php print l('[hardcoded] Farmacologie', 'collection/O1Vb4NCUOolkT7iXSTVZmj0M');?></li>
      <li><?php print l('[hardcoded] Lorem ipsum', 'collection/O1Vb4NCUOolkT7iXSTVZmj0M');?></li>
      <li><?php print l('[hardcoded] Dolor Sit Amet', 'collection/O1Vb4NCUOolkT7iXSTVZmj0M');?></li>
    </ul>
  </div>
</div>

<div class="asset-technical-information">
  <ul id="asset-tabs">
    <li>
      <?php print l('Description', 'asset/' . $fields['asset_id']->raw, array('fragment' => 'tab-metadata-dc', 'attributes' => array('name' => 'tab-metadata-dc'))); ?>
    </li>
    <li>
      <?php print l('More info', 'asset/' . $fields['asset_id']->raw, array('fragment' => 'tab-metadata-qdc', 'attributes' => array('name' => 'tab-metadata-qdc'))); ?>
    </li>
    <li>
      <?php print l('Technical info', 'asset/' . $fields['asset_id']->raw, array('fragment' => 'tab-technical-metadata', 'attributes' => array('name' => 'tab-technical-metadata'))); ?>
    </li>
  </ul>

  <div class="tab" id="tab-metadata-dc">
    <h2>Metadata DC</h2>
    <?php print $fields['metadata_dc']->content; ?>
  </div>

  <div class="tab" id="tab-metadata-qdc">
    <h2>Metadata QDC</h2>
    <?php print $fields['metadata_qdc']->content; ?>
  </div>

  <div class="tab" id="tab-technical-metadata">
    <h2>Technical metadata</h2>
    <?php print $fields['technical_metadata']->content; ?>
  </div>
</div>
<!--
<?php foreach ($fields as $id => $field): ?>
    <?php if (!empty($field->separator)): ?>
      <?php print $field->separator; ?>
    <?php endif; ?>

    <?php print $field->wrapper_prefix; ?>
      <?php print $field->label_html; ?>
      <?php print $field->content; ?>
    <?php print $field->wrapper_suffix; ?>
  <?php endforeach; ?>

 -->