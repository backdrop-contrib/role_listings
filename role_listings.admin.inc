<?php
/**
 * @file
 * Admin pages for displaying permissions and users by role.
 */

/**
 * Configuration form for the role listings settings.
 */
function role_listings_settings_form($form, &$form_state) {
  $form['#config'] = 'role_listings.settings';

  $user_roles = user_roles(TRUE);

  $form['permissions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Role permissions'),
  );
  $form['permissions']['permissions_pages'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Permissions pages'),
    '#description' => t('Create individual permissions pages for the roles checked above. This can improve page load time when there are many roles and many module permissions.'),
    '#options' => $user_roles,
    '#default_value' => config_get('role_listings.settings', 'permissions_pages'),
  );

  $extra_user_roles = $user_roles;
  unset($extra_user_roles['authenticated']);
  $form['user_lists'] = array(
    '#type' => 'fieldset',
    '#title' => t('User lists'),
  );
  $form['user_lists']['role_users'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Show role users'),
    '#description' => t('Show individual lists of users who have each of the checked roles.'),
    '#options' => $extra_user_roles,
    '#default_value' => config_get('role_listings.settings', 'role_users'),
  );
  $form['user_lists']['special_role_users'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Show special role users'),
    '#description' => t('Show a list of users who have any of these roles. If no roles are checked, this page will not be shown.'),
    '#options' => $extra_user_roles,
    '#default_value' => config_get('role_listings.settings', 'special_role_users'),
  );

  $form = system_settings_form($form);
  $form['#submit'][] = 'role_listings_settings_form_submit_extra';
  return $form;
}

/**
 * Extra processing after submitting the role listings settings form.
 */
function role_listings_settings_form_submit_extra($form, &$form_state) {
  $role_names = array_filter($form_state['values']['special_role_users']);
  _role_listings_set_special_roles($role_names);
  menu_rebuild();
}

/**
 * Returns a display of the users with special roles.
 */
function role_listings_special_role_users_view() {
  $view = views_get_view('role_user_accounts');
  return $view->preview('special');
}

/**
 * Returns a display of the users with a specific role.
 */
function role_listings_role_users_view($role_name) {
  $view = views_get_view('role_user_accounts');
  return $view->preview('by_role', array($role_name));
}
