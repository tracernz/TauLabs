"use strict;"

angular.module('BootFlasher')
 .controller('FlashFirmwareController', ['$scope', '$location', 'selectedBoard', function($scope, $location, selectedBoard) {
 	$scope.$on('$viewContentLoaded', function() {
        translate();
    });

    $scope.selectedBoard = selectedBoard;

    
}]);
