const theDiv = document.querySelector('.welcome');
const welcomeMsg = "WELCOME TO DAY FOR NIGHT CINEMA!";
let dynamicWelcome = "";

let i = 0;

// Making every char of the welcome Msg appear in sequance
function wm(char){
    if (dynamicWelcome <= welcomeMsg){

        dynamicWelcome = dynamicWelcome + welcomeMsg[i];
        theDiv.innerText = dynamicWelcome;
        i++
    }
    if (dynamicWelcome.length === welcomeMsg.length){
        clearInterval(counter);
    }

}



let counter = setInterval(wm, 60, welcomeMsg);


