<?php
// $Id: page.tpl.php 1817 2011-10-12 11:11:44Z thijs $
?>
<div id="header">
  <div class="header_content">
    <div class="site_logo">
      <?php print l(theme('image', array('path' => $logo, 'title' => $site_name, 'alt' => $site_name)), '<front>', array('html' => TRUE)); ?>
    </div>
    <?php print render($page['header']); ?>
  </div>
</div>
<div id="container">
  <?php if ($site_slogan): ?>
    <div class="slogan">
      <p><?php print $site_slogan; ?></p>
    </div>
  <?php endif; ?>

  <?php if ($breadcrumb): ?>
    <div id="breadcrumbs"><?php print $breadcrumb; ?></div>
  <?php endif; ?>

  <div id="content">
    <div id="page_content"><?php dsm($page); ?>
      <?php print $messages; ?>
      <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
      <?php print render($page['help']); ?>
      <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
      <?php print render($page['content']); ?>
    </div>
  </div>
  <div id="footer">
    <div class="mm_logo">
      <?php print theme('image', array('path' => $logo)); ?>
    </div>
    <?php print render($page['footer']); ?>
  </div>
</div>