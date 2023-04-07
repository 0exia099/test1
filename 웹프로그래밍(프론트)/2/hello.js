const btn = document.getElementById("btn1");
const img = document.getElementById("img1");
const img1 = img.src;

function onbtnClick(event){
    if(img.src == img1){
        btn.innerText = "판다로"
        img.src = "./IMG_0786.PNG";
        img.height="500";
        img.width="670";
    }
    else{
        btn.innerText = "책상으로"
        img.src = "./IMG_1211-2.PNG";
        img.height="500";
        img.width="670";
    }
}
btn.addEventListener("click", onbtnClick);