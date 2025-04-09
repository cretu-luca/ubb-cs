$(document).ready(function () {
  const images = [
    "images/0.png",
    "images/1.png",
    "images/2.png",
    "images/3.png",
    "images/4.png",
  ];

  const $track = $(".slider");
  const $popUpOverlay = $(".pop-up-overlay");
  const $popUpContent = $(".pop-up-content");
  const $selectionBox = $(".image-selection-box");
  const $addButton = $(".add-button");

  let imageIndex = 0;
  let isRunning = true;
  let animationId = null;
  let speed = 1;
  let indices = [];

  function animate() {
    const currentLeft = parseInt($track.css("left"));
    const $firstImage = $track.find(".image").first();
    const imageWidth = $firstImage.outerWidth(true);
    $track.css("left", currentLeft - speed + "px");

    if (currentLeft <= -imageWidth) {
      $firstImage.remove();
      $track.css("left", "15px");
      imageIndex = (imageIndex + 1) % images.length;
      $track.append(
        '<div class="image"><img src="' + images[imageIndex] + '" /></div>'
      );
    }

    if (isRunning) {
      animationId = requestAnimationFrame(animate);
    }
  }

  function setupSlider() {
    for (let i = 0; i < 3 * images.length; i++) {
      const index = i % images.length;
      $track.append(
        '<div class="image"><img src="' + images[index] + '" /></div>'
      );
    }

    $track.on("click", "img", function () {
      if (isRunning) {
        const imageSource = $(this).attr("src");
        showPopUp(imageSource);
      }
    });

    $popUpOverlay.on("click", function () {
      hidePopUp();
    });

    $addButton.on("click", function () {
      $.each($("select option:selected"), function () {
        images.push($(this).val());
      });

      console.log(images);
    });

    for (let i = 5; i < 15; i++) {
      $selectionBox.append(
        $("<option>", {
          value: "images/" + i + ".png",
          text: "images/" + i + ".png",
        })
      );
    }
  }

  function showPopUp(imageSource) {
    pauseAnimation();
    $popUpContent.html('<img src="' + imageSource + '" />');
    $popUpOverlay.css("display", "flex");
  }

  function hidePopUp() {
    $popUpOverlay.css("display", "none");
    resumeAnimation();
  }

  function startAnimation() {
    animationId = requestAnimationFrame(animate);
  }

  function pauseAnimation() {
    isRunning = false;
    cancelAnimationFrame(animationId);
  }

  function resumeAnimation() {
    isRunning = true;
    startAnimation();
  }

  setupSlider();
  startAnimation();
});
