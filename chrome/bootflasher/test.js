$(document).ready(function () {
	var boards = new BoardManager();

	$("#lol").click(function() {
		console.log(boards.getBoards({"arch": "stm32f1"}));
	});
});
