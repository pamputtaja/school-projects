// Add a class 'list' to the existing navigation link list
const navList = document.querySelector('nav ul');
navList.classList.add('list');

// Create a new link and insert it as the last item inside the navigation link list
const newLink = document.createElement('a');
newLink.href = 'http://localhost:3000/';
newLink.textContent = 'Localhost';

const listItem = document.createElement('li');
listItem.appendChild(newLink);
navList.appendChild(listItem);

// Insert a new list item with the text 'Item 0' as the first element of the ordered list with id 'ordered'
const orderedList = document.getElementById('ordered');
const newItem = document.createElement('li');
newItem.textContent = 'Item 0';
orderedList.insertBefore(newItem, orderedList.firstElementChild);

// Remove the class 'navi' from the todo list (unordered list with id 'todo')
const todoList = document.getElementById('todo');
todoList.classList.remove('navi');

// Delete the second list item from the todo list with text 'Item 2'
const todoItems = todoList.getElementsByTagName('li');
for (let i = 0; i < todoItems.length; i++) {
  if (todoItems[i].textContent === 'Item 2') {
    todoList.removeChild(todoItems[i]);
    break; // Exit the loop once the item is deleted
  }
}
