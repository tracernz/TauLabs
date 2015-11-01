"use strict;"

angular.module('BootFlasher')
 .controller('OperationSelectController', ['$scope', '$location', 'selectedBoard', function($scope, $location, selectedBoard) {
 	$scope.$on('$viewContentLoaded', function() {
        translate();
    });

    $scope.selectedBoard = selectedBoard;

    $scope.flashBootloader = function() {
    	if($scope.selectedBoard.hasUsbDfu())
    		$location.path("/flashBootloader");
    	else
    		$location.path("/serialInstructions");
    };

    $scope.flashFirmware = function() {
    	$location.path("/flashFirmware");
    };

    $scope.eraseEeprom = function() {
    	$location.path("/eraseEeprom");
    };
}]);
