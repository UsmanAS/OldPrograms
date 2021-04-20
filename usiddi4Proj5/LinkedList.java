/*
 * This file contains the User Interface code for the Infix Evaluation 
 * Project, Project 5 for CS 211 for Spring 2016, the data structure for
 * a linked list.
 * 
 * Date: 3/10/16
 * Usman Siddiqui
 */

import java.io.*;
import java.util.*;

class LinkedList{
  
  public class Node {
    public Node head;
    public Node next;
    public int data;
    public char op;
    
    public Node(){
      data = -1;
      next = null;
    }
    
    
    public Node(int val){
      next = null;
      data = val;
    }
    
    public void setNext(Node nextVal){
      next = nextVal;
    }
    
    public void setData(int val){
      data = val;
    }
    public void setData(char val){
      op = val;
    }
    public int isEmpty(){
      if(head == null)
        return 1;
      return 0;
    }
    
    public void push(int val){
      if(head == null){
        head.data = val;
        head.next = null;
      }
      else{
        Node temp = new Node(val);
        temp.setData(val);
        temp.setNext(head);
        head = temp;
      }
    }
    
    public int topVal(){
      return head.data;
    }
    
    public char topOp(){
      return head.op;
    }
    
    public void pop(){
      head = head.next;
    }
    public Node getNext(){
      return head.next;
    }
    
  }
  

  public Node createNode(){
    return new Node();
  }
  
  public void createOpStack(){
    opStack = createNode();
  }
  
  public void createValStack(){
    valStack = createNode();
  }
  Node opStack;
  Node valStack;
  
}   