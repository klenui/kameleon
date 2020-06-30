const Storage=require('storage');
const storage = new Storage();
storage.setItem('value1', 'abcd');
storage.setItem('value2', '1234');
const val1 = storage.getItem('value1');
const val2 = storage.getItem('value2');
console.log(`val1 : ${val1}`);
console.log(`val2 : ${val2}`);
