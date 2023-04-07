const images = [
    "0.png",
    "1.png",
    "2.png"
];

const chosenImage = images[Math.floor(Math.random() * images.length)];

//const bgImage = document.createElement("img");
//bgImage.src = `img/${chosenImage}`;

const bgImage = `img/${chosenImage}`;
document.querySelector("body").style.backgroundImage = `url('${bgImage}')`;

//document.body.appendChild(bgImage);