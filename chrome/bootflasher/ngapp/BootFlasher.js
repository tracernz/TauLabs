"use strict;"

var BootFlasherApp = angular.module('BootFlasher', ['ngRoute'], function($provide) {
	// Prevent Angular from sniffing for the history API
	// since it's not supported in packaged apps.
	$provide.decorator('$window', function($delegate) {
		$delegate.history = null;
		return $delegate;
	});
});

BootFlasherApp.config(['$routeProvider', function($routeProvider) {
	$routeProvider

	.when('/selectBoard', {
		templateUrl: 'templates/board_select.html', controller: 'BoardSelectController'
	})

	.when('/selectOperation', {
		templateUrl: 'templates/operation_select.html', controller: 'OperationSelectController'
	})

	.when('/flashFirmware', {
		templateUrl: 'templates/flash_firmware.html', controller: 'FlashFirmwareController'
	})

	.when('/flashBootloader', {
		templateUrl: 'templates/flash_bootloader.html', controller: 'FlashBootloaderController'
	})

	.otherwise({
		redirectTo: '/selectBoard'
	});
	
}]);

BootFlasherApp.value("selectedBoard", {});
