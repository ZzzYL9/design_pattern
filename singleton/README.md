
## 设计模式： 单例模式 --对象创建型模式

### 保证一个类只有一个实例，并提供一个访问它的全局访问点。首先，需要保证一个类只有一个实例，在类中，要构造一个实例，就必须调用类的构造函数，如此，为了防止在外部调用类的构造函数而构造实例，需要将构造函数的访问权限标记为protected或private；最后，需要提供要给全局访问点，就需要在类中定义一个static函数，返回在类内部唯一构造的实例

优点：
    
    ① 在内存中只有一个对象，节省内存空间
    
    ② 避免频繁的创建销毁对象，可以提高性能
    
    ③ 避免对共享资源的多重占用
    
    ④ 可以全局访问
    
适用场景：

    ① 需要频繁实例化然后销毁的对象
    
    ② 创建对象耗时过多或者资源消耗过多，但又经常用到的对象
    
    ③ 有状态的工具类对象
    
    ④ 频繁访问数据库或文件的对象
    
    ⑤ 以及其他要求只有一个对象的场景
