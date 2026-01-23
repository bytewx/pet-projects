package main

import (
	"fmt"
	"sync"
	"time"
)

func worker(id int, jobs <-chan int, results chan<- Result, wg *sync.WaitGroup) {
	defer wg.Done()

	for job := range jobs {
		time.Sleep(80 * time.Millisecond)

		val := job * job

		fmt.Printf("Worker %d processed job %d -> %d\n", id, job, val)

		results <- Result{job: job, value: val, worker: id}
	}
}

type Result struct {
	job    int
	value  int
	worker int
}

func main() {
	const numWorkers = 3
	const numJobs = 10

	jobs := make(chan int)
	results := make(chan Result)

	var wg sync.WaitGroup

	// "fan-out", run workers (multiple "jobs" readers)
	for i := 1; i <= numWorkers; i++ {
		wg.Add(1)
		go worker(i, jobs, results, &wg)
	}

	// run a producer to send "jobs"
	go func() {
		for j := 1; j <= numJobs; j++ {
			jobs <- j
		}
		close(jobs)
	}()

	// close "results" channel only when all workers are done
	go func() {
		wg.Wait()
		close(results)
	}()

	// "fan-in", collect all results in one place
	sum := 0
	count := 0

	for r := range results {
		sum += r.value
		count++
	}

	fmt.Println("\nDone")
	fmt.Println("Count results: ", count)
	fmt.Println("Sum: ", sum)
}
