import 'dart:io';

void main(){

  //DATATYPES
  print('WELCOME');
  stdout.write('welcome');
  var name=stdin.readLineSync();
  print("Welcome,$name");
  var prajwal= new Human();
  int?a;
  BigInt b;
  var n="prajwal";//first initialized datatype is taken
  n="ra";
  var S;//dynamic datatype
   S="name";
   S=7;

   //LISTS
   var listNmae=["prajwal",30,40];
   var names=[];
    names.addAll(listNmae);//add all elemnts of prevoius list also we can store differnt types of data at last
    names.add(20);
    names.insertAll(2, listNmae);//we can provide index here
    names[2]="ramesh"
    names.replaceRange(1, 4, [contents])//
    names.removeRange(1, 3);

    //MAPS
  var map_name={
    'key1':'key',
    'key2':1,
    'key3':3.5
  };
  map_name['key1']='prajwal';//override key
  print(map_name['key2']);
  print(map_name.isEmpty);

  var mapNmae = Map();//this is also method here Map() is constructor of class Map
}


//CLASSES AND OBJECTS
class Human{
   Human();//default constructor
}
class myclass{
  void printname(String na){
    print(na);
  }
}

const names=[];
names.add(1);//not possible in const keyword but possible in final keyword
