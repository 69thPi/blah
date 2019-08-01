var slideIndex = 1;
  showSlides(slideIndex);   /*display slides*/

function plusSlides(n) {  /*left and right buttons*/
  showSlides(slideIndex += n);
}

function currentSlide(n) {  /*move arbitarily to a slide*/
  showSlides(slideIndex = n);
}

function showSlides(n) {
  var i;
  var slides = document.getElementsByClassName("slide");
  var dots = document.getElementsByClassName("dot");
  if (n > slides.length) {slideIndex = 1}
  if (n < 1) {slideIndex = slides.length}
  for (i = 0; i < slides.length; i++) {
      slides[i].style.display = "none";
  }
  for (i = 0; i < dots.length; i++) {
      dots[i].className = dots[i].className.replace(" active", "");
  }
  slides[slideIndex-1].style.display = "initial";
  dots[slideIndex-1].className += " active";
}
