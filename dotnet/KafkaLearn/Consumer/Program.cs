using Confluent.Kafka;

var topic = "test";
var config = new ConsumerConfig
{
    BootstrapServers = "localhost:9092",
    GroupId = "csharp",
    AutoOffsetReset = AutoOffsetReset.Earliest
};

using(var consumer = new ConsumerBuilder<Ignore, string>(config).Build())
{
    consumer.Subscribe(topic);

    CancellationTokenSource cts = new CancellationTokenSource();
    Console.CancelKeyPress += (_, e) =>
    {
        e.Cancel = true;
        cts.Cancel();
    };

    try
    {
        while (true)
        {
            var consumerResult = consumer.Consume(cts.Token);
            Console.WriteLine($"Consumed event from topic {topic} with key {consumerResult.Message.Key,-10} and value {consumerResult.Message.Value}");
        }
    }
    catch(OperationCanceledException)
    {
        consumer.Close();
        Console.WriteLine("Consumer was cancelled");
    }  
}