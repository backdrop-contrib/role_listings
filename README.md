Role Listings
======================

This module adds listings for individual roles to the administration pages, specifically:

* Individual role permission pages as tabs of /admin/config/people/permissions

Lists of users who have particular roles:

* A page listing users with any of a specified set of roles.
* Individual pages listing all users for selected individual roles.

On Backdrop, the User accounts listing at admin/people allows you to filter by role, so the individual role lists aren't strictly necessary, but it can be useful to have them directly accessible as tabs.

All of the pages above can be turned on or off on the configuration page for this module.

Installation
------------

- Install this module using [the official Backdrop CMS instructions](  https://backdropcms.org/guide/modules).

- Visit the configuration page under Administration > Configuration > User accounts >
  Role Listings (admin/config/people/role-listings) to specify
  - the roles to receive individual permissions pages,
  - the roles in the "Special roles" list, and/or
  - to turn on or off the display of individual role listings of users.

Related Modules
-------------

- The [Filter Permissions](https://backdropcms.org/project/filter_perms) module provides a similar function for permissions pages, allowing filtering of permissions by role and/or by module. (In Backdrop 1.24.x and higher, filtering by keyword is provided by Backdrop core).

Issues
------

Bugs and feature requests should be reported in [the Issue Queue](https://github.com/backdrop-contrib/role_listings/issues).

Current Maintainers
-------------------

- [Robert J. Lang](https://github.com/bugfolder).

Credits
-------

- Written for Backdrop CMS by [Robert J. Lang](https://github.com/bugfolder).

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.

