"use strict;"

angular.module('BootFlasher')
 .controller('BoardSelectController', ['$scope', '$location', 'selectedBoard', function($scope, $location, selectedBoard) {
 	$scope.$on('$viewContentLoaded', function() {
        translate();
    });

 	var boardMgr = new BoardManager();

 	$scope.boards = [{name: ""}];
 	$scope.selectedBoard = $scope.boards[0]; //This sets the default value of the select in the ui

 	$scope.boards.push.apply($scope.boards, boardMgr.excludeBoards({shortName: "stm32dfu"}));

 	$scope.continue = function() {
 		for(var p in $scope.selectedBoard)
 			selectedBoard[p] = $scope.selectedBoard[p];
 		$location.path("/selectOperation");
 	}
}]);