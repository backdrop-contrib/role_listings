<?php

/**
 * @file
 * Admin page for displaying users by role
 */


/**
 * Configuration form for the role listings settings.
 */
function role_listings_settings_form($form, &$form_state) {
  $form['#config'] = 'role_listings.settings';
  $form[] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Users'),
    '#description' => t('Enter the maximum number of users to list for any role.'),
    '#default_value' => config_get('role_listings.settings', 'role_listings_max'),
    '#element_validate' => array('element_validate_integer_positive'),
  );

  return system_settings_form($form);
}


/**
 * Display a list of all roles with links to their page listings.
 */
function role_listings_display() {
  $max = config_get('role_listings.settings', 'role_listings_max');
  $build[] = array(
    '#markup' => t('These are the roles (beyond the two default roles) and the user accounts (up to @max users <a href="/admin/config/people/role-listings">[change limit]</a>) that have that role.',
      array('@max' => $max)),
    '#prefix' => '<p>',
    '#suffix' => '</p>',
  );

  $header = array(
    array('data' => t('Role')),
    array('data' => t('User names')),
    array('data' => t('User emails')),
  );

  $rows = array();
  $roles = user_roles(TRUE, NULL, TRUE);
  foreach ($roles as $rid => $role) {
    if ($rid == BACKDROP_AUTHENTICATED_ROLE) {
      continue;
    }
    $row_data = array(
      'label' => $role->label,
      'accounts' => array(),
      'emails' => array(),
    );
    $uids = db_query('
      SELECT DISTINCT(ur.uid)
      FROM {users_roles} AS ur
      WHERE ur.role = :role
      ', array(':role' => $rid))
      ->fetchCol();
    if (count($uids) <= $max) {
      $accounts = user_load_multiple($uids);
      foreach ($accounts as $account) {
        $row_data['accounts'][] = l($account->name, "/user/{$account->uid}");
        $row_data['emails'][] = $account->mail;
      }
    }
    else {
      $row_data['accounts'][] = l(t('details'), "admin/people/users/{$role->rid}");
      $row_data['emails'][] = '—';
    }
    $rows[] = array(
      array('data' => $row_data['label']),
      array('data' => implode('<br>', $row_data['accounts'])),
      array('data' => implode('<br>', $row_data['emails'])),
    );
  }

  $build[] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('None'),
  );

  return $build;
}
