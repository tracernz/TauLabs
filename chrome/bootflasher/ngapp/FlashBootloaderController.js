"use strict;"

angular.module('BootFlasher')
 .controller('FlashBootloaderController', ['$scope', '$location', 'selectedBoard', function($scope, $location, selectedBoard) {
 	$scope.$on('$viewContentLoaded', function() {
        translate();
    });

    $scope.selectedBoard = selectedBoard;

    
}]);
