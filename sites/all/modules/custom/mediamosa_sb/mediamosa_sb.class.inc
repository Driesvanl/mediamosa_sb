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
 * Simple static class for main functions of MediaMosa Site Builder.
 */
class mediamosa_sb {

  /**
   * Returns the title of the asset using the metadata.
   *
   * @param simplexmlelement $asset
   *   The asset in simplexmlelement.
   *
   * @return
   *   The title or ''.
   *
   * @see mediamosa_ck::get_asset_title()
   */
  static public function get_asset_title($asset) {
    $title = mediamosa_ck::get_asset_title($asset);
    return $title === '' ? t('[no title]') : t($title);
  }

  /**
   * This wrapper is indended when in the future if we want to tell the user
   * that something went wrong and log the problem. We might want to make
   * options for the admin in which we log the error, but will not bore the user
   * with the error.
   */
  static public function watchdog_error($message, array $variables = array()) {
    // Call our CK version.
    mediamosa_ck::watchdog_error($message, $variables);
  }

  /**
   * Return the metadata languages.
   *
   * @return
   *   Return an array with languages.
   */
  static public function get_metdata_languages_options() {
    return array(
      '' => t('Undefined'),
      'ab' => t('Abkhaz'),
      'aa' => t('Afar'),
      'af' => t('Afrikaans'),
      'ak' => t('Akan'),
      'sq' => t('Albanian'),
      'am' => t('Amharic'),
      'ar' => t('Arabic'),
      'an' => t('Aragonese'),
      'hy' => t('Armenian'),
      'as' => t('Assamese'),
      'av' => t('Avaric'),
      'ae' => t('Avestan'),
      'ay' => t('Aymara'),
      'az' => t('Azerbaijani'),
      'bm' => t('Bambara'),
      'ba' => t('Bashkir'),
      'eu' => t('Basque'),
      'be' => t('Belarusian'),
      'bn' => t('Bengali'),
      'bh' => t('Bihari'),
      'bi' => t('Bislama'),
      'bs' => t('Bosnian'),
      'br' => t('Breton'),
      'bg' => t('Bulgarian'),
      'my' => t('Burmese'),
      'ca' => t('Catalan'),
      'ch' => t('Chamorro'),
      'ce' => t('Chechen'),
      'ny' => t('Chichewa'),
      'zh' => t('Chinese'),
      'cv' => t('Chuvash'),
      'kw' => t('Cornish'),
      'co' => t('Corsican'),
      'cr' => t('Cree'),
      'hr' => t('Croatian'),
      'cs' => t('Czech'),
      'da' => t('Danish'),
      'dv' => t('Divehi'),
      'nl' => t('Dutch'),
      'dz' => t('Dzongkha'),
      'en' => t('English'),
      'eo' => t('Esperanto'),
      'et' => t('Estonian'),
      'ee' => t('Ewe'),
      'fo' => t('Faroese'),
      'fj' => t('Fijian'),
      'fi' => t('Finnish'),
      'fr' => t('French'),
      'ff' => t('Fula'),
      'gl' => t('Galician'),
      'ka' => t('Georgian'),
      'de' => t('German'),
      'el' => t('Greek'),
      'gn' => t('Guaraní'),
      'gu' => t('Gujarati'),
      'ht' => t('Haitian'),
      'ha' => t('Hausa'),
      'he' => t('Hebrew'),
      'hz' => t('Herero'),
      'hi' => t('Hindi'),
      'ho' => t('Hiri Motu'),
      'hu' => t('Hungarian'),
      'ia' => t('Interlingua'),
      'id' => t('Indonesian'),
      'ie' => t('Interlingue'),
      'ga' => t('Irish'),
      'ig' => t('Igbo'),
      'ik' => t('Inupiaq'),
      'io' => t('Ido'),
      'is' => t('Icelandic'),
      'it' => t('Italian'),
      'iu' => t('Inuktitut'),
      'ja' => t('Japanese'),
      'jv' => t('Javanese'),
      'kl' => t('Kalaallisut'),
      'kn' => t('Kannada'),
      'kr' => t('Kanuri'),
      'ks' => t('Kashmiri'),
      'kk' => t('Kazakh'),
      'km' => t('Khmer'),
      'ki' => t('Kikuyu'),
      'rw' => t('Kinyarwanda'),
      'ky' => t('Kirghiz'),
      'kv' => t('Komi'),
      'kg' => t('Kongo'),
      'ko' => t('Korean'),
      'ku' => t('Kurdish'),
      'kj' => t('Kwanyama'),
      'la' => t('Latin'),
      'lb' => t('Luxembourgish'),
      'lg' => t('Luganda'),
      'li' => t('Limburgish'),
      'ln' => t('Lingala'),
      'lo' => t('Lao'),
      'lt' => t('Lithuanian'),
      'lu' => t('Luba-Katanga'),
      'lv' => t('Latvian'),
      'gv' => t('Manx'),
      'mk' => t('Macedonian'),
      'mg' => t('Malagasy'),
      'ms' => t('Malay'),
      'ml' => t('Malayalam'),
      'mt' => t('Maltese'),
      'mr' => t('Marathi'),
      'mh' => t('Marshallese'),
      'mn' => t('Mongolian'),
      'na' => t('Nauru'),
      'nv' => t('Navajo'),
      'nb' => t('Norwegian Bokmål'),
      'nd' => t('North Ndebele'),
      'ne' => t('Nepali'),
      'ng' => t('Ndonga'),
      'nn' => t('Norwegian Nynorsk'),
      'no' => t('Norwegian'),
      'ii' => t('Nuosu'),
      'nr' => t('South Ndebele'),
      'oc' => t('Occitan'),
      'oj' => t('Ojibwe'),
      'om' => t('Oromo'),
      'or' => t('Oriya'),
      'os' => t('Ossetian'),
      'pa' => t('Panjabi'),
      'fa' => t('Persian'),
      'pl' => t('Polish'),
      'ps' => t('Pashto'),
      'pt' => t('Portuguese'),
      'qu' => t('Quechua'),
      'rm' => t('Romansh'),
      'rn' => t('Kirundi'),
      'ro' => t('Romanian'),
      'ru' => t('Russian'),
      'sa' => t('Sanskrit'),
      'sc' => t('Sardinian'),
      'sd' => t('Sindhi'),
      'se' => t('Northern Sami'),
      'sm' => t('Samoan'),
      'sg' => t('Sango'),
      'sr' => t('Serbian'),
      'gd' => t('Gaelic'),
      'sn' => t('Shona'),
      'si' => t('Sinhala'),
      'sk' => t('Slovak'),
      'sl' => t('Slovene'),
      'so' => t('Somali'),
      'st' => t('Southern Sotho'),
      'es' => t('Spanish'),
      'su' => t('Sundanese'),
      'sw' => t('Swahili'),
      'ss' => t('Swati'),
      'sv' => t('Swedish'),
      'ta' => t('Tamil'),
      'te' => t('Telugu'),
      'tg' => t('Tajik'),
      'th' => t('Thai'),
      'ti' => t('Tigrinya'),
      'bo' => t('Tibetan'),
      'tk' => t('Turkmen'),
      'tl' => t('Tagalog'),
      'tn' => t('Tswana'),
      'to' => t('Tonga'),
      'tr' => t('Turkish'),
      'ts' => t('Tsonga'),
      'tt' => t('Tatar'),
      'tw' => t('Twi'),
      'ty' => t('Tahitian'),
      'ug' => t('Uighur'),
      'uk' => t('Ukrainian'),
      'ur' => t('Urdu'),
      'uz' => t('Uzbek'),
      've' => t('Venda'),
      'vi' => t('Vietnamese'),
      'vo' => t('Volapük'),
      'wa' => t('Walloon'),
      'cy' => t('Welsh'),
      'wo' => t('Wolof'),
      'fy' => t('Western Frisian'),
      'xh' => t('Xhosa'),
      'yi' => t('Yiddish'),
      'yo' => t('Yoruba'),
      'za' => t('Zhuang, Chuang'),
      'zu' => t('Zulu')
     );
  }

  /**
   * Post the metadata from form submited fields.
   */
  static public function post_metadata($values, $asset_id) {
    // Options + metadata for write.
    $options = array('action' => 'replace');

    // Get the metadata def.
    $metadata_fields = mediamosa_ck::get_metadata_fields();

    foreach ($metadata_fields as $prefix => $metadata_field) {
      foreach ($metadata_field['fields'] as $name => $type) {
        // Build name.
        $prefixed_name = $prefix . '_' . $name;

        if (!isset($values[$prefixed_name]) || $values[$prefixed_name] === '') {
          continue;
        }

        // Set.
        $options[$name] = $values[$prefixed_name];
      }
    }

    // Do request.
    if (!MediaMosaSbConnectorWrapper::update_metadata($asset_id, $options)) {
      mediamosa_sb::watchdog_error('Unable to save metadata.');
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Set access on mediafile.
   *
   * @param $values
   * @param $asset_id
   * @param $mediafile_id
   *
   * @return
   */
  static public function post_access($values, $asset_id) {

    // Save state isprivate to asset.
    $options = array(
      'isprivate' => (isset($values['is_visible']) && !empty($values['is_visible']) ? FALSE : TRUE),
    );

    MediaMosaSbConnectorWrapper::update_asset($asset_id, $options);

    // Get the mediafiles.
    $mediafile_ids = MediaMosaSbConnectorWrapper::get_asset_mediafile_ids($asset_id);

    // Domains and realms.
    $acl_domain_realm = array();

    // acl users.
    $acl_user_id = array();

    $acl_domain = trim($values['acl_domain']);
    $acl_realm = trim($values['acl_realm']);
    $acl_user = trim($values['acl_user']);

    if (!empty($acl_domain)) {
      $acl_domain_realm[] = $acl_domain;
    }
    if (!empty($acl_realm)) {
      $acl_domain_realm[] = $acl_realm;
    }
    $acl_domain_realm = implode(',', $acl_domain_realm);

    foreach ($mediafile_ids as $mediafile_id) {
      if (!MediaMosaSbConnectorWrapper::set_access_control($mediafile_id, mediamosa_ck::session_user_id(), $acl_domain_realm, $acl_user)) {
        mediamosa_sb::watchdog_error('Unable to save access for mediafile with ID @mediafile_id.', array('@mediafile_id' => $mediafile_id));
        return FALSE;
      }
    }

    return TRUE;
  }

  /**
   * Post transcode & still.
   *
   * @param $values
   * @param $asset_id
   * @param $mediafile_id
   */
  static public function post_media($values, $asset_id) {

    // Get existing mediafiles transcodes.
    $current_used_transcode_profiles = MediaMosaSbConnectorWrapper::get_asset_current_used_transcode_profiles($asset_id);

    // Get the original mediafile_id.
    $mediafile_id_original = reset(MediaMosaSbConnectorWrapper::get_asset_mediafile_ids_original($asset_id));
/*
    if (!empty($mediafile_id_original)) {
      foreach ($values as $name => $profile_id) {
        if (drupal_substr($name, 0, strlen('active_')) == 'active_') {
          // If not in $current_used_transcode_profiles, then we can start it.
          if ($current_used_transcode_profiles[$profile_id]) {
            continue;
          }

          // Start transcode job.
          MediaMosaSbConnectorWrapper::create_transcode($mediafile_id_original, array('profile_id' => $profile_id));
        }
      }
    }
*/
  }
}

