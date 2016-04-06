Dictionary{
  constructor: make dict
  destructor: delete dict
  flush()
  check()
  update()
  
}

LRU{
  constructor: build LL
  destructor: delete LL
  update(way)
  
}

FullyAss{
  constructor: make LRU and dict
  destructor: delete LRU and dict
  
}

Way{
  constructor make LRU and dict
  destructor delete LRU and dict
  
}

Victim{
  constructor
  destructor
  
}

Cache{
  constructor(?)
  destructor
  bool check(addr, size)
  replace(addr)
  
}

CacheSystem{
  constructor
  destructor
  public:
    newInput(op, addr, size)
    dataReporting()
  priv:
    readD()
    readI()
    write()
}
