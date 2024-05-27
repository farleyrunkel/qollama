#ifndef OLLAMA_CLIENT_H
#define OLLAMA_CLIENT_H

#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include <asio.hpp>
#include <fstream>
#include <stdexcept>

namespace ollama {

using json = nlohmann::json;


std::map<std::string, std::string> defaultHeaders_ = {
    {"User-Agent", "My ASIO Client"},
    {"Accept", "application/json"},
    {"Content-Type", "application/json"}
};


class SyncClient {
public:
    SyncClient(const std::string& host, bool follow_redirects = true);
    ~SyncClient();

    nlohmann::json generate(const std::string& model, const std::string& prompt = "", const std::string& system = "", const std::string& template_ = "");
    nlohmann::json chat(const std::string& model, const std::vector<nlohmann::json>& messages);
    nlohmann::json embeddings(const std::string& model, const std::string& prompt);
    nlohmann::json pull(const std::string& model, bool insecure = false);
    nlohmann::json push(const std::string& model, bool insecure = false);
    nlohmann::json create(const std::string& model, const std::string& path);
    nlohmann::json delete_model(const std::string& model);
    nlohmann::json list();
    nlohmann::json copy(const std::string& source, const std::string& destination);
    nlohmann::json show(const std::string& model);

private:
    std::string host_;
    bool follow_redirects_;
    std::string userAgent_;
    std::string accept_;
    std::string contentType_;

    void setHeaders(asio::streambuf& request) {
        std::ostream request_stream(&request);

        // Set standard headers
        for (const auto& header : defaultHeaders_) {
            request_stream << header.first << ": " << header.second << "\r\n";
        }

        // Add custom headers
        // for (const auto& header : customHeaders_) {
        //     request_stream << header.first << ": " << header.second << "\r\n";
        // }

        // End of headers
        request_stream << "\r\n";
    }

};






SyncClient::SyncClient(const std::string& host, bool follow_redirects) : host_(host), follow_redirects_(follow_redirects) {
    userAgent_ = "My ASIO Client";
    accept_ = "application/json";
    contentType_ = "application/json";
}

SyncClient::~SyncClient() {}

json SyncClient::generate(const std::string& model, const std::string& prompt, const std::string& system, const std::string& template_) {
    asio::io_context io;
    asio::ip::tcp::socket socket(io);
    asio::connect(socket, host_, "80");

    asio::streambuf request;
    std::ostream request_stream(&request);

    request_stream << "POST /generate HTTP/1.0\r\n";
    request_stream << "Host: " << host_ << "\r\n";
    request_stream << "User-Agent: " << userAgent_ << "\r\n";
    request_stream << "Accept: " << accept_ << "\r\n";
    request_stream << "Content-Type: " << contentType_ << "\r\n";
    request_stream << "\r\n";

    json payload = {
        {"model", model},
        {"prompt", prompt},
        {"system", system},
        {"template", template_}
    };

    request_stream << payload.dump();

    asio::write(socket, request);

    asio::streambuf response;
    asio::read_until(socket, response, "\r\n\r\n");

    std::istream response_stream(&response);
    json response_json;
    response_stream >> response_json;

    return response_json;
}

json SyncClient::chat(const std::string& model, const std::vector<json>& messages) {
    asio::io_context io;
    asio::ip::tcp::socket socket(io);
    asio::connect(socket, host_, "80");

    asio::streambuf request;
    std::ostream request_stream(&request);

    request_stream << "POST /chat HTTP/1.0\r\n";
    request_stream << "Host: " << host_ << "\r\n";
    request_stream << "User-Agent: " << userAgent_ << "\r\n";
    request_stream << "Accept: " << accept_ << "\r\n";
    request_stream << "Content-Type: " << contentType_ << "\r\n";
    request_stream << "\r\n";

    json payload = {
        {"model", model},
        {"messages", messages}
    };

    request_stream << payload.dump();

    asio::write(socket, request);

    asio::streambuf response;
    asio::read_until(socket, response, "\r\n\r\n");

    std::istream response_stream(&response);
    json response_json;
    response_stream >> response_json;

    return response_json;
}
json SyncClient::embeddings(const std::string& model, const std::string& prompt) {
    asio::io_context io;
    asio::ip::tcp::socket socket(io);
    asio::connect(socket, host_, "80");

    asio::streambuf request;
    std::ostream request_stream(&request);

    request_stream << "POST /embeddings HTTP/1.0\r\n";
    request_stream << "Host: " << host_ << "\r\n";
    request_stream << "User-Agent: " << userAgent_ << "\r\n";
    request_stream << "Accept: " << accept_ << "\r\n";
    request_stream << "Content-Type: " << contentType_ << "\r\n";
    request_stream << "\r\n";

    json payload = {
        {"model", model},
        {"prompt", prompt}
    };

    request_stream << payload.dump();

    asio::write(socket, request);

    asio::streambuf response;
    asio::read_until(socket, response, "\r\n\r\n");

    std::istream response_stream(&response);
    json response_json;
    response_stream >> response_json;

    return response_json;
}
json SyncClient::pull(const std::string& model, bool insecure) {
    std::string url = "/models/" + model;
    if (insecure) {
        url += "/insecure";
    }

    asio::io_context io;
    asio::ip::tcp::socket socket(io);
    asio::connect(socket, host_, "80");

    asio::streambuf request;
    std::ostream request_stream(&request);

    request_stream << "GET " << url << " HTTP/1.0\r\n";
    request_stream << "Host: " << host_ << "\r\n";
    request_stream << "User-Agent: " << userAgent_ << "\r\n";
    request_stream << "Accept: " << accept_ << "\r\n";
    request_stream << "\r\n";

    asio::write(socket, request);

    asio::streambuf response;
    asio::read_until(socket, response, "\r\n\r\n");

    std::istream response_stream(&response);
    json response_json;
    response_stream >> response_json;

    return response_json;
}
json SyncClient::push(const std::string& model, bool insecure) {
    std::string url = "/models/" + model;
    if (insecure) {
        url += "/insecure";
    }

    asio::io_context io;
    asio::ip::tcp::socket socket(io);
    asio::connect(socket, host_, "80");

    asio::streambuf request;
    std::ostream request_stream(&request);

    request_stream << "PUT " << url << " HTTP/1.0\r\n";
    request_stream << "Host: " << host_ << "\r\n";
    request_stream << "User-Agent: " << userAgent_ << "\r\n";
    request_stream << "Accept: " << accept_ << "\r\n";
    request_stream << "Content-Type: application/octet-stream\r\n";
    request_stream << "\r\n";

    // Assuming the model data is stored in a file
    std::ifstream model_file(model, std::ios::binary);
    if (!model_file) {
        throw std::runtime_error("Failed to open model file");
    }

    asio::write(socket, request);

    // Send the model data
    char buffer[4096];
    while (model_file.read(buffer, 4096)) {
        asio::write(socket, asio::buffer(buffer, model_file.gcount()));
    }

    asio::streambuf response;
    asio::read_until(socket, response, "\r\n\r\n");

    std::istream response_stream(&response);
    json response_json;
    response_stream >> response_json;

    return response_json;
}

json SyncClient::create(const std::string& model, const std::string& path) {
    asio::io_context io;
    asio::ip::tcp::socket socket(io);
    asio::connect(socket, host_, "80");

    asio::streambuf request;
    std::ostream request_stream(&request);

    request_stream << "POST /models HTTP/1.0\r\n";
    request_stream << "Host: " << host_ << "\r\n";
    request_stream << "User-Agent: " << userAgent_ << "\r\n";
    request_stream << "Accept: " << accept_ << "\r\n";
    request_stream << "Content-Type: application/json\r\n";
    request_stream << "\r\n";

    json payload = {
        {"model", model},
        {"path", path}
    };

    request_stream << payload.dump();

    asio::write(socket, request);

    asio::streambuf response;
    asio::read_until(socket, response, "\r\n\r\n");

    std::istream response_stream(&response);
    json response_json;
    response_stream >> response_json;

    return response_json;
}

json SyncClient::delete_model(const std::string& model) {
    // Implement me!
}

json SyncClient::list() {
    // Implement me!
}

json SyncClient::copy(const std::string& source, const std::string& destination) {
    // Implement me!
}

json SyncClient::show(const std::string& model) {
    // Implement me!
}





















class AsyncClient {
public:
    AsyncClient(const std::string& host, bool follow_redirects = true);
    ~AsyncClient();

    void generate_async(const std::string& model, const std::string& prompt = "", const std::string& system = "", const std::string& template_ = "", std::function<void(nlohmann::json)> callback);
    void chat_async(const std::string& model, const std::vector<nlohmann::json>& messages, std::function<void(nlohmann::json)> callback);
    void embeddings_async(const std::string& model, const std::string& prompt, std::function<void(nlohmann::json)> callback);
    void pull_async(const std::string& model, bool insecure = false, std::function<void(nlohmann::json)> callback);
    void push_async(const std::string& model, bool insecure = false, std::function<void(nlohmann::json)> callback);
    void create_async(const std::string& model, const std::string& path, std::function<void(nlohmann::json)> callback);
    void delete_model_async(const std::string& model, std::function<void(nlohmann::json)> callback);
    void list_async(std::function<void(nlohmann::json)> callback);
    void copy_async(const std::string& source, const std::string& destination, std::function<void(nlohmann::json)> callback);
    void show_async(const std::string& model, std::function<void(nlohmann::json)> callback);

private:
    std::string host_;
    bool follow_redirects_;
    asio::io_context io_context_;
    asio::ip::tcp::resolver resolver_;
    asio::ip::tcp::socket socket_;
    std::string userAgent_;
    std::string accept_;
    std::string contentType_;



};

} // namespace ollama














#endif // OLLAMA_CLIENT_H
