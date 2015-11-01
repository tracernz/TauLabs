angular.module('BootFlasher')
 .controller('BoardSelectController', ['$scope', function($scope) {
 	var boardMgr = new BoardManager();

 	$scope.boards = [{name: ""}];
 	var selectedBoard = $scope.boards[0]; //This sets the default value of the select in the ui

 	$scope.boards.push.apply($scope.boards, boardMgr.excludeBoards({shortName: "stm32dfu"}));
}]);