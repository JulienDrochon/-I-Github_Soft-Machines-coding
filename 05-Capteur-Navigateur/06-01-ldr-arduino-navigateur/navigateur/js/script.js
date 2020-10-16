setInterval(function () {
  let tailleTexte = mapData(dataFromArduino[0], 0, 400, 0, 40);
  let interlettrage = mapData(dataFromArduino[1], 0, 400, 0, 40);

  document.querySelector("#monTexteAchanger").style.fontSize =
    tailleTexte + "px";
  document.querySelector("#monTexteAchanger").style.fontSize =
    interlettrage + "px";
}, 50);
