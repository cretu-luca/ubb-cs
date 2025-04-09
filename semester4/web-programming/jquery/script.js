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
  let imageIndex = 0;
  let isRunning = true;
  let animationId = null;

  function setupSlider() {
    for (let i = 0; i < images.length + 1; i++) {
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
    const speed = 1;

    function animate() {
      const currentLeft = parseInt($track.css("left") || "0");
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
