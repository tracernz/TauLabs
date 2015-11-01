translate = function() {
	$("[i18n]:not(.i18n-replaced)").each(function() {
		$(this).html(chrome.i18n.getMessage($(this).attr("i18n")));
		$(this).addClass("i18n-replaced");
	});
};
