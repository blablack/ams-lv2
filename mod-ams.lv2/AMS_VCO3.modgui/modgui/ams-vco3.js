function (event) {
  if (event.type == 'change') {
    var ledLine = document.getElementById("led-line")
    if (event.symbol === "waveForm") {
      if (event.value === 2 || event.value === 3) {
        ledLine.style.backgroundPosition = "left center";
      } else {
        ledLine.style.backgroundPosition = "right center";
      }
    }
	}
}
