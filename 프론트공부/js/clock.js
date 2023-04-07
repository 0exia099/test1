const clock = document.querySelector("h1#clock");

function getClock() {
    const date = new Date();
    const hours = String(date.getHours()).padStart();
    const minutes = String(date.getMinutes()).padStart(2,"0");
    const seconds = String(date.getSeconds()).padStart(2,"0");
    clock.innerText = `${hours}:${minutes}:${seconds}`;
}

//setInterval(sayHello, 5000);  // 5초마다(ms단위) 해당함수 실행
//setTimeout(sayHello, 5000); // 5초후 한번만 실행
getClock();
setInterval(getClock, 1000);