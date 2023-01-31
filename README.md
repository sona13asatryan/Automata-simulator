# Automata-simulator

This project is a simulator of Automata machines, which accepts as its input a file of the following configuration:

a<sub>1</sub>, a<sub>2</sub>, a<sub>3</sub>, a<sub>4</sub>, ...  
  
b<sub>1</sub>, b<sub>2</sub>, b<sub>3</sub>, b<sub>4</sub>, ...  
  
q<sub>1</sub>, q<sub>2</sub> ...  
  

b<sub>i<sub>11</sub></sub>, q<sub>j<sub>11</sub></sub> | b<sub>i<sub>12</sub></sub>, q<sub>j<sub>12</sub></sub> | b<sub>i<sub>13</sub></sub>, q<sub>j<sub>13</sub></sub> | b<sub>i<sub>14</sub></sub>, q<sub>j<sub>14</sub></sub>  
b<sub>i<sub>21</sub></sub>, q<sub>j<sub>21</sub></sub> | b<sub>i<sub>22</sub></sub>, q<sub>j<sub>22</sub></sub> | b<sub>i<sub>23</sub></sub>, q<sub>j<sub>23</sub></sub> | b<sub>i<sub>24</sub></sub>, q<sub>j<sub>24</sub></sub>  

Where a<sub>i</sub>, b<sub>i</sub> are characters excluding commas and whitespaces,  
q<sub>i</sub> are substrings that also don't contain commas and whitespaces.

The file can also contain some input tape examples after the table.  
You can see an example of a configuration in [Test.txt](https://github.com/sona13asatryan/Automata-simulator/blob/main/Test.txt).  

This test discribes the following automata.

```mermaid  
graph LR;  
  A((q1)) -->|a/1| B((q2));
  A -->|b/0| B;
  B -->|a/0| A;
  B -->|b/1| A;
   
```
