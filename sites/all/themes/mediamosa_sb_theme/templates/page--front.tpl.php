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
      <h1><?php print $site_slogan; ?></h1>
    </div>
  <?php endif; ?>
  <div id="content">
    <div id="spotlight">
      <div class="region">
        <?php print render($page['highlighted']); ?>
      </div>
    </div>
    <div id="page_content">
      <div class="region region-content">
        <?php print $messages; ?>

        <?php hide($page['content']['system_main']); ?>
        <?php print render($page['content']); ?>
      </div>
    </div>
  </div>
  <div id="footer">
    <div class="mm_logo">
      <?php print theme('image', array('path' => path_to_theme() .'/images/mm_logo.png'))?>
    </div>
    <?php print render($page['footer']); ?>
  </div>
</div>