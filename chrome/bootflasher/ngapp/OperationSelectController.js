angular.module('BootFlasher')
 .controller('OperationSelectController', ['$scope', '$location', 'selectedBoard', function($scope, $location, selectedBoard) {
 	$scope.$on('$viewContentLoaded', function() {
        translate();
    });

    $scope.selectedBoard = selectedBoard;

    $scope.flashBootloader = function() {
    	$location.path("/flashBootloader");
    };

    $scope.flashFirmware = function() {
    	$location.path("/flashFirmware");
    };

    $scope.eraseEeprom = function() {
    	$location.path("/eraseEeprom");
    };
}]);