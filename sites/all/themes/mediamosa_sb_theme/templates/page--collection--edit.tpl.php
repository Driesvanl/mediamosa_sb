<div id="header">
  <div class="header_content">
    <div class="site_logo">
      <?php print l(theme('image', array('path' => $logo, 'title' => $site_name, 'alt' => $site_name)), '<front>', array('html' => TRUE)); ?>
    </div>

    <?php if (user_is_logged_in()): ?>
    <div class="user-custom-navigation">
      <?php print l(t('My Videos'), 'myassets'); ?>&nbsp;|&nbsp;<?php print l(t('My Collections'), 'mycollections'); ?>&nbsp;|&nbsp;<?php print l(t('My account'), 'user'); ?>
    </div>
    <?php print l(t('Upload'), 'asset/upload', array('attributes' => array('class' => array('user-login-button')))); ?>
    <?php else:?>
      <?php print l(t('Sign in'), 'user', array('attributes' => array('class' => array('user-login-button')))); ?>
    <?php endif;?>

    <select id="language-picker">
      <option>EN</option>
      <option selected>NL</option>
    </select>

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
    <div id="page_content">
      <?php print $messages; ?>
      <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
      <?php print render($page['help']); ?>
      <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

<!--       <ul class="item-navigation">
        <li><span><?php //print l(t('View'), 'view', array('attributes' => array('class' => 'view'))); ?></span></li>
      </ul> -->
        <?php print render($page['content']); ?>
      <?php if (!empty($page['sidebar_first'])): ?>
        <div class="collection-information">
          <?php print render($page['sidebar_first']); ?>
        </div>
      <?php endif; ?>
    </div>
  </div>
  <div id="footer">
    <div class="mm_logo">
      <?php print theme('image', array('path' => $logo)); ?>
    </div>
    <?php print render($page['footer']); ?>
  </div>
</div>