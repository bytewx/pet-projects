package main

import (
	"fmt"
	"sync"
	"time"
)

func printMany(name string, times int, wg *sync.WaitGroup) {
	defer wg.Done()

	for i := 1; i <= times; i++ {
		time.Sleep(1 * time.Millisecond)

		fmt.Printf("%s %d\n", name, i)
	}
}

func main() {
	names := []string{"A", "B", "C", "D", "E"}

	var wg sync.WaitGroup
	wg.Add(len(names))

	for _, n := range names {
		go printMany(n, 5, &wg)
	}

	wg.Wait()
	fmt.Println("Done")
}
