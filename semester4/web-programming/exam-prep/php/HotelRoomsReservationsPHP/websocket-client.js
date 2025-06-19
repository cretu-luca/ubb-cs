/**
 * Simple WebSocket polyfill for PHP
 * This creates a WebSocket-like interface using AJAX
 */
class PHPWebSocket {
    constructor(url) {
        this.url = url;
        this.isConnected = false;
        this.listeners = {
            'open': [],
            'message': [],
            'close': [],
            'error': []
        };
        
        // Auto connect
        this.connect();
        
        // Start polling
        this.pollInterval = setInterval(() => this.poll(), 1000);
    }
    
    connect() {
        const xhr = new XMLHttpRequest();
        xhr.open('GET', this.url + '?action=connect', true);
        xhr.onreadystatechange = () => {
            if (xhr.readyState === 4) {
                if (xhr.status === 200) {
                    this.isConnected = true;
                    this.triggerEvent('open', {});
                } else {
                    this.triggerEvent('error', { error: 'Connection failed' });
                }
            }
        };
        xhr.send();
    }
    
    poll() {
        if (!this.isConnected) return;
        
        const xhr = new XMLHttpRequest();
        xhr.open('GET', this.url + '?action=poll&t=' + new Date().getTime(), true);
        xhr.onreadystatechange = () => {
            if (xhr.readyState === 4 && xhr.status === 200) {
                try {
                    const response = JSON.parse(xhr.responseText);
                    if (response.hasMessage) {
                        this.triggerEvent('message', { data: response.message });
                    }
                } catch (e) {
                    // Ignore parsing errors
                }
            }
        };
        xhr.send();
    }
    
    send(message) {
        const xhr = new XMLHttpRequest();
        xhr.open('POST', this.url, true);
        xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
        xhr.onreadystatechange = () => {
            if (xhr.readyState === 4 && xhr.status !== 200) {
                this.triggerEvent('error', { error: 'Send failed' });
            }
        };
        xhr.send('action=send&message=' + encodeURIComponent(message));
    }
    
    close() {
        clearInterval(this.pollInterval);
        this.isConnected = false;
        this.triggerEvent('close', {});
    }
    
    addEventListener(event, callback) {
        if (this.listeners[event]) {
            this.listeners[event].push(callback);
        }
    }
    
    triggerEvent(event, data) {
        if (this.listeners[event]) {
            for (const callback of this.listeners[event]) {
                callback(data);
            }
        }
    }
    
    // Standard WebSocket API compatibility
    get onopen() { return this.listeners.open[0]; }
    set onopen(callback) { 
        this.listeners.open = [callback]; 
    }
    
    get onmessage() { return this.listeners.message[0]; }
    set onmessage(callback) { 
        this.listeners.message = [callback]; 
    }
    
    get onclose() { return this.listeners.close[0]; }
    set onclose(callback) { 
        this.listeners.close = [callback]; 
    }
    
    get onerror() { return this.listeners.error[0]; }
    set onerror(callback) { 
        this.listeners.error = [callback]; 
    }
} 