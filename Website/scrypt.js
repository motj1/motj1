
function successMessage() {
    alert ("Thank you for your responce it has been sent and we will get back to you as soon as we can.");
}

function getContent(i) {
	return document.getElementById("name"+i).innerHTML;
}


function SaveItem() {
	var name = document.forms.ShoppingList.name.value;
	const item = document.forms.ShoppingList.data.value + "  " + document.forms.ShoppingList.cost.value + "  " + document.forms.ShoppingList.max.value;
	let max = document.forms.ShoppingList.max.value;
	console.log(document.forms.ShoppingList.data.value);
	if (document.forms.ShoppingList.data.value <= max && document.forms.ShoppingList.data.value != 0) {
		localStorage.setItem(name, item);
		alert ("Item saved navigate to the cart to see it.");
	} else if (document.forms.ShoppingList.data.value == 0){
		alert ("Please enter amount");
	} else {
		alert ("Too many items");
	}
}

function countnum(name) {
	var num = 0;
	
	for (let i = 0; i < 10; i ++){
		if (localStorage.getItem(name+i) != null){
			num ++;
		}
	}
	
	return num;
}

function SaveComment(){
	let name = document.forms.ShoppingList.name.value + countnum(document.forms.ShoppingList.name.value);
	let data = document.forms.ShoppingList.data.value;
	
	localStorage.setItem(name, data);
}

function RemoveItem() {
	var name = document.forms.ShoppingList.name.value;

	document.forms.ShoppingList.data.value = localStorage.removeItem(name);
}

function ClearAll() {
	localStorage.clear();
}

function plus(i) {
	let name = getContent(i);
	let text = localStorage.getItem(name);
	var myArray = text.split("  ");
	
	if (parseInt(myArray[0], 10) < parseInt(myArray[2]), 10) {
		myArray[0] = parseInt(myArray[0], 10) + 1;
		let txt = myArray[0] + "  " + myArray[1] + "  " + myArray[2];
		localStorage.setItem(name, txt);
	} else {
		alert ("Too many items");
		console.log(myArray[0], myArray[2]);
	}
	doShowAll();
}

function minus(i) {
	let name = getContent(i);
	let text = localStorage.getItem(name);
	var myArray = text.split("  ");
	
	if ((parseInt(myArray[0], 10)-1) > 0) {
		myArray[0] = parseInt(myArray[0], 10) - 1;
		let txt = myArray[0] + "  " + myArray[1] + "  " + myArray[2];
		localStorage.setItem(name, txt);
	} else {
		localStorage.removeItem(name);
	}
	doShowAll();
}

function doShowAll() {
	var key = "";
	var list = "<table class='cart'><tr><th><b>Item</b></th><th><b>Amount</b></th><th><b>Price ($)</b></th><th><b>Total ($)</b></th></tr>\n";
	var i = 0;

	for (i = 0; i <= localStorage.length-1; i++) {

		key = localStorage.key(i);
		
		let text = localStorage.getItem(key);
		
		let myArray = text.split("  ");
		if (key === "Blood Orange"){
			list += "<tr><td><img src='Images/Fruits/BloodOrange.png' alt='Blood Orange' width='210' height='200'><p id='name"+i+"'>Blood Orange</p>"
		} else {
			list += "<tr><td><img src='Images/Fruits/" + key + ".png' alt='Fruit.' width='230' height='200'><p id='name"+i+"'>" + key + "</p>"
		}
		list += "</td>\n<td>\n<button class='minus' onClick='minus("+i+")' style='float: left'>-</button><b>"
				+ myArray[0] + "</b>\n<button class='plus' onClick='plus("+i+")' style=''>+</button></td>\n<td><b>"
				+ myArray[1] + "</b></td>\n<td class='total'><b>"
				+ (parseFloat(myArray[0])*parseFloat(myArray[1])).toFixed(2) + "</b></td></tr>\n";
	}
	if (list == "<table class='cart'><tr><th><b>Item</b></th><th><b>Amount</b></th><th><b>Price ($)</b></th><th><b>Total ($)</b></th></tr>\n") {
		list += "<tr><td><i>empty</i></td>\n<td><i>empty</i></td>\n<td><i>empty</i></td>\n<td><i>empty</i></td></tr>\n";
	}
	document.getElementById('cart').innerHTML = list+"</table>\n";
}

function makeForm() {
	var code = "<label for='email'><b>Email</b></label>\n<input type='email' id='email' name='email' placeholder='Email..' autocomplete='off'>\n";
	var key = "";
	var items = "";
	var ammounts = "";
	var prices = "";
	var total = 0;

	for (let i = 0; i <= localStorage.length-1; i++) {

		key = localStorage.key(i);
		
		let text = localStorage.getItem(key);
		
		let myArray = text.split("  ");
		items += key + ",";
		ammounts += myArray[0] + ",";
		prices += myArray[1] + ",";
		total += (parseFloat(myArray[0])*parseFloat(myArray[1]));
	}
	code += "<input type='hidden' name='Items' value=" + items + ">\n<input type='hidden' name='Ammounts' value=" + ammounts + ">\n<input type='hidden' name='Prices' value=" + prices + ">\n<input type='hidden' name='Total' value=" + total + ">\n"
	document.getElementById('myForm').innerHTML = code;
}

function checkEmail(email){
	if (/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/.test(email)){
		return true
	}
    alert("You have entered an invalid email address!")
    return false
}

function login(){
	var uid = document.forms.myForm.uname.value;
	var upass = document.forms.myForm.pword.value;
	if (uid == "0" && upass == "123456789"){
		alert("Logging in");
		location.href = "EDash.html";
	} else {
		alert("Wrong password");
		alert("Right username: 0, Right password: 123456789")
	}
}
