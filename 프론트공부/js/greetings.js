const loginForm = document.querySelector("#login-form");
const loginInput = document.querySelector("#login-form input");
const greeting = document.querySelector("#greeting");
const link = document.querySelector("a");

const USERNAME_KEY = "username";
const HIDDEN_CLASSNAME = "hidden";

function paintGreetings(username){
    //greeting.innerText = "Hello, " + id;  // 문자열을 아래처럼도 가능.
    greeting.innerText = `Hello, ${username}`;    //1번 옆의 `기호 사용. 영어일때만 나옴(한글일때는 ₩로나옴)
    greeting.classList.remove(HIDDEN_CLASSNAME);
}

// html의 기능을 사용하기위해 form사용, 버튼대신 인풋submit타입사용.
// html에서 form을 사용하면 인풋에서 엔터또는 인풋submit버튼을 누르면 자동으로 submit된다. -> 새로고침
// 따라서 클릭 이벤트말고 submit에서 새로고침 안되게하고 버튼눌린거 동작 하게한다.
function onLoginSubmit(event) {// 인자를 주면 JS에서 자동으로 기본이벤트인자 채워줌
    event.preventDefault();    // 이벤트의 기본 행동 발생 막기(submit에서는 새로고침이 막아짐)
    loginForm.classList.add(HIDDEN_CLASSNAME);  // css의 hidden으로 아이디 입력하면 입력 칸 없애기
    const username = loginInput.value;
    localStorage.setItem(USERNAME_KEY, username); // 로컬스토리지에 id저장. getItem으로 가져오고 removeItem지울 수 있다.
    paintGreetings(username);
}

function onLinkClick(event){
    event.preventDefault();
}

link.addEventListener("click", onLinkClick);

const savedUsername = localStorage.getItem(USERNAME_KEY);

if(savedUsername === null){
    loginForm.classList.remove(HIDDEN_CLASSNAME);
    loginForm.addEventListener("submit", onLoginSubmit);
}
else{
    paintGreetings(savedUsername);
}