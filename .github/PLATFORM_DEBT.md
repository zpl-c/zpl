# Platform debt

This file analyses and describes which platforms lack what functionality that ZPL implements.

## General

* Process module is implemented only for Windows at the moment.

## Linux

## OpenBSD

* **zpl_fs_copy** fails to work due to missing `sendfile` call replacement.

## Emscripten

* [NOT-FIXABLE] Threading is disabled

## Android

* [NOT-FIXABLE] Threading is disabled
