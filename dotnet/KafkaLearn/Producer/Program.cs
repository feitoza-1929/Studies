using Confluent.Kafka;

var topic = "test";
var config = new ProducerConfig
{
    BootstrapServers = "localhost:9092"
};

using(var producer = new ProducerBuilder<Null, string>(config).Build())
{
    producer.Produce(topic, new Message<Null, string> { Value = "Hello World!" });
    producer.Flush();
    Console.WriteLine("Message produced");
}