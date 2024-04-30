const alljoyn = require('./node_modules/alljoyn/alljoyn');

// Inicializa o bus AllJoyn
const bus = new alljoyn.BusAttachment('myApp', true);

// Conecta-se ao daemon AllJoyn
bus.connect();

// Define o nome do serviço
const serviceName = 'com.example.MyService';

// Define a interface do serviço
const interfaceName = 'com.example.MyInterface';

// Adiciona a interface ao bus
bus.createInterface(interfaceName);

// Adiciona um método à interface
bus.addMethod(interfaceName, 'sendMessage', 's', 's', ['message'], [], function(message, callback) {
  console.log('Mensagem recebida:', message);
  callback(null, 'Mensagem recebida com sucesso!');
});


// Registra o serviço
var busObject = {};
busObject[interfaceName] = {
  sendMessage: function(message, callback) {
    console.log('Mensagem enviada:', message);
    callback(null, 'Mensagem recebida com sucesso!');
  }
};

bus.registerBusObject('/example', busObject);


// Inicia o loop de eventos
bus.on('lost', () => {
  console.log('Conexão perdida com o daemon AllJoyn');
});

