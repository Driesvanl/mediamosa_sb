
(function ($) {
  Drupal.color = {
    logoChanged: false,
    callback: function(context, settings, form, farb, height, width) {
      // Change the logo to be the real one.
      if (!this.logoChanged) {
        $('#preview #preview-logo img').attr('src', Drupal.settings.color.logo);
        this.logoChanged = true;
      }
      // Remove the logo if the setting is toggled off. 
      if (Drupal.settings.color.logo == null) {
        $('div').remove('#preview-logo');
      }
      
      // Header background
      $('#preview #preview-header', form).css('background-color', $('#palette input[name="palette[header_bg]"]', form).val());
      
      // Slogan background
      $('#preview #preview-slogan', form).css('background-color', $('#palette input[name="palette[sloganbar]"]', form).val());
      
      // Slogan text
      $('#preview #preview-slogan h1', form).css('color', $('#palette input[name="palette[slogantext]"]', form).val());
      
      // UI background
      $('#preview #preview-featured', form).css('background-color', $('#palette input[name="palette[box]"]', form).val());

      // Video Hover Effect
      $('#preview #preview-video-overlay', form).css('background-color', $('#palette input[name="palette[videohover]"]', form).val());

      // Links
      $('#preview a', form).css('color', $('#palette input[name="palette[link]"]', form).val());
      
      // Primary Text
      $('#preview p', form).css('color', $('#palette input[name="palette[primary_text]"]', form).val());

      // Secondary Text
      $('#preview .preview-created', form).css('color', $('#palette input[name="palette[secondary_text]"]', form).val());

      // Tertiary Text
      $('#preview .preview-views-count', form).css('color', $('#palette input[name="palette[tertiary_text]"]', form).val());
      
      
      
      
      // Solid background.
     // $('#preview', form).css('backgroundColor', $('#palette input[name="palette[bg]"]', form).val());

      // Text preview.
     // $('#preview #preview-main h2', form).css('color', $('#palette input[name="palette[heading]"]', form).val());
     // $('#preview #preview-content a', form).css('color', $('#palette input[name="palette[link]"]', form).val());

      // Sidebar block.
     // $('#preview #preview-sidebar #preview-block', form).css('background-color', $('#palette input[name="palette[sidebar]"]', form).val());
     // $('#preview #preview-sidebar #preview-block', form).css('border-color', $('#palette input[name="palette[sidebarborders]"]', form).val());

      // Footer wrapper background.
      //$('#preview #preview-footer-wrapper', form).css('background-color', $('#palette input[name="palette[footer]"]', form).val());

      // CSS3 Gradients.
     // var gradient_start = $('#palette input[name="palette[top]"]', form).val();
    //  var gradient_end = $('#palette input[name="palette[bottom]"]', form).val();

     // $('#preview #preview-header', form).attr('style', "background-color: " + gradient_start + "; background-image: -webkit-gradient(linear, 0% 0%, 0% 100%, from(" + gradient_start + "), to(" + gradient_end + ")); background-image: -moz-linear-gradient(-90deg, " + gradient_start + ", " + gradient_end + ");");

      //$('#preview #preview-site-name', form).css('color', $('#palette input[name="palette[titleslogan]"]', form).val());
    }
  };
})(jQuery);
