
## 设计模式： 中介者模式 --对象行为型模式

### 中介者模式使用一个中介对象来封装一系列对象的交互，从而使各对象不需要显式的相互引用，从而使得对象耦合松散，而且可以独立地改变对象之间的交互。该模式是用来降低多个对象类之间的通信复杂性。

### 中介者模式与外观模式的区别：
    
    外观模式是对一个子系统进行抽象，从而提供了一个更为方便的接口；外观模式的协议是单向的，即外观模式向子系统提出请求，但反过来则不行；
    而对于中介者模式，是进行多个对象之间的协作，通信是多向的

![Image](https://github.com/ZzzYL9/design_pattern/blob/master/class_images/mediator.png)

### Mediator: 中介者，它定义了一个接口用于各个Colleague对象通信
### ConcreteMediator: 具体的中介者，它通过协调各Colleague对象实现协作行为；并了解和维护它的各个Colleague
### Colleague：同事类，每一个同事类都知道它的中介者对象，每一个同事对象在需要与其他的同事通信的时候，而是与它的中介者通信

优点：

    ① 降低了类的复杂度，将一对多转化成了一对一
    
    ② 各个类之间的解耦
    
    ③ 符合迪米特原则
    
缺点：

    ① 中介者会庞大，变得难以维护
    
    ② 如果中介者类出现问题，将会导致所有相关类出问题

使用场景：

    ① 一组对象以定义良好但是复杂的方式进行通信，产生的相互依赖关系结构混乱且难以理解
    
    ② 一个对象引用其他很多对象并且直接与这些对象通信，导致难以复用该对象
    
    ③ 想定制一个分布在多个类中的行为，而又不想生成太多的子类