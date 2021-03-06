<?php
/**
 * @file
 * demo_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function demo_core_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index().
 */
function demo_core_default_search_api_index() {
  $items = array();
  $items['default_node_index'] = entity_import('search_api_index', '{
    "name" : "Default node index",
    "machine_name" : "default_node_index",
    "description" : "An automatically created search index for indexing node data. Might be configured to specific needs.",
    "server" : "demo",
    "item_type" : "node",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "50",
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 1,
          "weight" : "-10",
          "settings" : {
            "default" : "0",
            "bundles" : {
              "author" : "author",
              "event" : "event",
              "page" : "page",
              "story" : "story"
            }
          }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_language_control" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "lang_field" : "", "languages" : [] }
        },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "field_story_summary" : true,
              "body:value" : true,
              "field_location:name" : true,
              "field_tags:name" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_story_summary" : true,
              "body:value" : true,
              "field_location:name" : true,
              "field_tags:name" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 1,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_verification_status" : true,
              "field_location" : true,
              "field_tags" : true,
              "field_story_summary" : true,
              "body:value" : true,
              "field_verification_status:name" : true,
              "field_location:name" : true,
              "field_tags:name" : true
            },
            "spaces" : "[^\\\\p{L}\\\\p{N}-]",
            "ignorable" : ""
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_story_summary" : true,
              "body:value" : true,
              "field_location:name" : true,
              "field_tags:name" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        }
      },
      "fields" : {
        "type" : { "type" : "string" },
        "title" : { "type" : "text", "boost" : "5.0" },
        "status" : { "type" : "integer" },
        "promote" : { "type" : "boolean" },
        "sticky" : { "type" : "boolean" },
        "created" : { "type" : "date" },
        "changed" : { "type" : "date" },
        "author" : { "type" : "integer", "entity_type" : "user" },
        "field_post_author" : { "type" : "integer", "entity_type" : "node" },
        "field_story_summary" : { "type" : "text" },
        "field_location" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_verification_status" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_what_description" : { "type" : "text" },
        "field_what_posts" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_when_posts" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_where_posts" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_author_rating" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "search_api_language" : { "type" : "string" },
        "body:value" : { "type" : "text" },
        "field_location:name" : { "type" : "text", "boost" : "2.0" },
        "field_tags:name" : { "type" : "list\\u003Ctext\\u003E", "boost" : "3.0" },
        "field_verification_status:name" : { "type" : "text" },
        "field_what_posts:title" : { "type" : "list\\u003Ctext\\u003E" },
        "field_when_posts:title" : { "type" : "list\\u003Ctext\\u003E" },
        "field_where_posts:title" : { "type" : "list\\u003Ctext\\u003E" }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function demo_core_default_search_api_server() {
  $items = array();
  $items['demo'] = entity_import('search_api_server', '{
    "name" : "demo",
    "machine_name" : "demo",
    "description" : "",
    "class" : "search_api_solr_service",
    "options" : {
      "host" : "localhost",
      "port" : "8983",
      "path" : "",
      "http_user" : "",
      "http_pass" : "",
      "excerpt" : 0,
      "retrieve_data" : 0,
      "highlight_data" : 0
    },
    "enabled" : "1"
  }');
  return $items;
}
