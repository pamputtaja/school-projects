const button_inc = document.getElementById("increment");
const button_dec = document.getElementById("decrement");
const button_res = document.getElementById("reset");
const counter = document.getElementById("counter");
let counter_int = 0;

button_inc.addEventListener("click", function() {
    if(counter_int === 5) {
        counter_int = -5;
    } else {
        counter_int++;
    }   
    counter.textContent = counter_int;
})

button_dec.addEventListener("click", function() {
    if(counter_int === -5) {
        counter_int = 5;
    } else {
        counter_int--;
    }   
    counter.textContent = counter_int;
})

button_res.addEventListener("click", function() {
    counter_int = 0;
    counter.textContent = counter_int;
})