
let board = [
  ['','',''],
  ['','',''],
  ['','',''],
];
let w;//=width/3;
let h;//=height/3;
let firstPlayerToMove={
  0:'O',
  1:'X'
}
let ai='X';
let human='O';
let currentPlayer=human;
let first=getRandomIntInclusive(0,1);
currentPlayer=firstPlayerToMove[first];
//console.log(currentPlayer + ' ' + first + ' ' + firstPlayerToMove[first]);


function setup() {
  createCanvas(400, 400);
  w=width/3;
  h=height/3;
  if(currentPlayer==ai){
     bestMove();
   }
}

function equals3(a,b,c){
  return (a==b && b==c && a!='');
}

function checkWinner(){
  let winner=null;
  // horizontalno
  for(let i=0;i<3;i++){
    if(equals3(board[i][0], board[i][1], board[i][2])){
      winner=board[i][0];
    }
  }
  // vertikalno
  for(let i=0;i<3;i++){
    if(equals3(board[0][i], board[1][i], board[2][i])){
      winner=board[0][i];
    }
  }
  // dijagonala1
    if(equals3(board[0][0], board[1][1], board[2][2])){
      winner=board[0][0];
    }
  // dijagonala2
    if(equals3(board[2][0], board[1][1], board[0][2])){
      winner=board[2][0];
    }

    let openSpots=0;
    for(let i=0;i<3;i++){
      for(let j=0;j<3;j++){
        if(board[i][j]=='')
          openSpots++;
      }
    }
  
  if(winner==null && openSpots==0){
    return 'tie';
  }else
    return winner;
}

function getRandomIntInclusive(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min + 1) + min); //The maximum is inclusive and the minimum is inclusive
}

function mousePressed(){
  if(currentPlayer==human){

    let i=floor(mouseX/w);
    let j=floor(mouseY/h);
    //igrac
    if(board[i][j]==''){
      board[i][j]=human;
      currentPlayer=ai;
      //ai
      var delayInMilliseconds = 1000; //1 sekunda 

      setTimeout(function() {
        bestMove();
            }, delayInMilliseconds);
      
      
    }
  }
}

function draw() {
  background(220);
  
  line(w,0,w,height);
  line(w*2,0,w*2,height);
  line(0,h,width,h);
  line(0,h*2,width,h*2);

  for(let j=0;j<3;j++){
    for(let i=0;i<3;i++){
      let x=w*i+w/2;
      let y=h*j+h/2;
      
      let spot=board[i][j];
      strokeWeight(4);
      
      if(spot==human){
        noFill();
        ellipse(x,y,w/2);
      }else if(spot==ai){
        let xr=w/4;
        line(x-xr,y-xr,x+xr,y+xr);
        line(x+xr,y-xr,x-xr,y+xr);
        
      }
    }
  }
  
  let result=checkWinner();
  if(result != null){
    noLoop();
    console.log(result);
    let resultP=createP('');
    resultP.style('font-size','32pt');
    if(result=='tie'){
      resultP.html('tie');
    }else{
      resultP.html(`${result}`);
    }
  }    
}