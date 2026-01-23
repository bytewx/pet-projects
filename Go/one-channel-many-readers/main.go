package main

import (
	"fmt"
	"sync"
	"time"
)

func worker(id int, jobs <-chan int, wg *sync.WaitGroup) {
	defer wg.Done()

	for job := range jobs {
		time.Sleep(50 * time.Millisecond)

		fmt.Printf("worker %d got job %d\n", id, job)
	}
}

func main() {
	jobs := make(chan int)

	var wg sync.WaitGroup

	numWorkers := 3
	numJobs := 12

	for i := 1; i <= numWorkers; i++ {
		wg.Add(1)
		go worker(i, jobs, &wg)
	}

	for j := 1; j <= numJobs; j++ {
		jobs <- j
	}
	close(jobs)

	wg.Wait()

	fmt.Println("All jobs are done.")
}
